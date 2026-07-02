struct SPSIn
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv : TEXCOORD0;
};

struct SPSOut
{
    float4 albedo : SV_Target0;
    float4 normal : SV_Target1;
    float4 metaricShadowSmooth : SV_Target2;
};

#include "../ModelVSCommon.h"

Texture2D<float4> g_albedo : register(t0);
Texture2D<float4> g_normal : register(t1);
Texture2D<float4> g_spacular : register(t2);
sampler g_sampler : register(s0);

static const int dither_table[4][4] = {
    { 0, 32, 8, 40 }, { 48, 16, 56, 24 },
    { 12, 44, 4, 36 }, { 60, 28, 52, 20 }
};

cbuffer CustomBuffer : register(b1)
{
    float g_opacity;
    float g_isDither;
    float g_smoothness;
    float g_time; // ★C++の WaterConstantBuffer と順番を合わせる
};

float3 GetNormalFromNormalMap(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    // ★ 1. UVをタイリングして目を細かくするならここ（例: 8.0倍にザラザラにする）
    // もし今のままで良ければ、下の SampleLevel の uv を tiledUV に変えずに uv のままでOK
    float2 tiledUV = uv * 2.0f; 

    // テクスチャから法線を取得
    float3 binSpaceNormal = g_normal.SampleLevel(g_sampler, tiledUV, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

    // ★ 2. ここで強度を調整！ (0.1 ～ 0.3 あたりに下げると汚れっぽさが消える)
    float normalStrength = 0.2f;
    binSpaceNormal.x *= normalStrength;
    binSpaceNormal.y *= normalStrength;

    // 最後にTBN変換してワールド空間の法線にする
    return tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;
}

SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer)
{
    SPSIn psIn;
    
// VSMainCore内
float4 localPos = vsIn.pos;

// 「上」方向（Y軸）に対してのみ波の変位を加える
// sinの引数には、水平面である X と Z を使う
float wave = sin(localPos.x * 0.05f + g_time * 1.5f) + sin(localPos.z * 5.05f + g_time * 1.2f);

localPos.z += wave * 2.0f; // ★Z軸にのみ加算する

// その後、ワールド行列を適用
float4 worldPos = mul(mWorldLocal, localPos);
    
    // ビュー・プロジェクション変換
    psIn.pos = mul(mView, worldPos);
    psIn.pos = mul(mProj, psIn.pos);
    
    CalcVertexNormalTangentBiNormalInWorldSpace(psIn.normal, psIn.tangent, psIn.biNormal, mWorldLocal, vsIn.normal, vsIn.tangent, vsIn.biNormal, isUsePreComputedVertexBuffer);
    psIn.uv = vsIn.uv;
    return psIn;
}

SPSOut PSMainCore(SPSIn psIn, int isShadowReciever)
{
    SPSOut psOut;
    // 赤色代入を削除して、元のテクスチャサンプリングに戻す
    psOut.albedo = g_albedo.Sample(g_sampler, psIn.uv);
    
    // ...以降の処理（アルファテストなどは一旦そのまま）
    uint d_x = (uint) psIn.pos.x % 2;
    uint d_y = (uint) psIn.pos.y % 2;
    clip(0.5f - (float) dither_table[d_y][d_x] / 64.0f); // 簡易化

    psOut.albedo.w = psIn.pos.z;
    psOut.normal.xyz = GetNormalFromNormalMap(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);
    psOut.normal.w = 1.0f;
    psOut.metaricShadowSmooth = g_spacular.Sample(g_sampler, psIn.uv);
    
    psOut.metaricShadowSmooth.r = 0.0f;
    psOut.metaricShadowSmooth.g = 255.0f * (float) isShadowReciever;
    psOut.metaricShadowSmooth.b = 0.8f;
    psOut.metaricShadowSmooth.a = 0.3f;
    return psOut;
}

SPSOut PSMain(SPSIn psIn) { return PSMainCore(psIn, 0); }
SPSOut PSMainShadowReciever(SPSIn psIn) { return PSMainCore(psIn, 1); }