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
    float g_smoothness; // ★ 1. ここに追加（paddingと入れ替え、または調整）
    float padding;      // タイトに詰めるために float1 に変更（合計4つで16バイトのアライメントを維持）
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
    psIn.pos = CalcVertexPositionInWorldSpace(vsIn.pos, mWorldLocal, isUsePreComputedVertexBuffer);
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    CalcVertexNormalTangentBiNormalInWorldSpace(psIn.normal, psIn.tangent, psIn.biNormal, mWorldLocal, vsIn.normal, vsIn.tangent, vsIn.biNormal, isUsePreComputedVertexBuffer);
    psIn.uv = vsIn.uv;
    return psIn;
}

SPSOut PSMainCore(SPSIn psIn, int isShadowReciever)
{
    SPSOut psOut;
    // �e�N�X�`���̐F���T���v���i�����ŃA���t�@�l���擾�����j
    psOut.albedo = g_albedo.Sample(g_sampler, psIn.uv);
    
    uint d_x = (uint) psIn.pos.x % 2;
    uint d_y = (uint) psIn.pos.y % 2;

    // --- 0.5f �ł͂Ȃ��A�e�N�X�`���̃A���t�@�l(psOut.albedo.a)���g�� ---
    clip(psOut.albedo.a - (float) dither_table[d_y][d_x] / 64.0f);
    // ------------------------------------------------------------

    psOut.albedo.w = psIn.pos.z;
    psOut.normal.xyz = GetNormalFromNormalMap(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);
    psOut.normal.w = 1.0f;
   // 1. テクスチャをそのままサンプリング
    psOut.metaricShadowSmooth = g_spacular.Sample(g_sampler, psIn.uv);

    // ★ ここでチェック！
    // もし魚の元のテクスチャのGチャンネル（あるいはAチャンネル）が、他と違って「ほぼ空っぽ(0.1未満)」なら…
    
    psOut.metaricShadowSmooth.r = 0.0f;  // メタリック＝0（金属ではなく、生き物の質感にする）
    psOut.metaricShadowSmooth.g = 255.0f * (float) isShadowReciever; // 影の設定はそのまま維持
    psOut.metaricShadowSmooth.b = 0.8f;  // スムースネス＝0.8（数値を 0.5 ～ 0.9 の間で上げると、ツルツルにテカる！）
    psOut.metaricShadowSmooth.a = 0.3f;
    return psOut;
}

SPSOut PSMain(SPSIn psIn) { return PSMainCore(psIn, 0); }
SPSOut PSMainShadowReciever(SPSIn psIn) { return PSMainCore(psIn, 1); }