///////////////////////////////////////
// PBRベースのディファードライティング
///////////////////////////////////////


///////////////////////////////////////
// 定数
///////////////////////////////////////

static const int NUM_REFLECTION_TEXTURE = 5;    // 映り込みテクスチャ。
///////////////////////////////////////
// 構造体。
///////////////////////////////////////

//頂点シェーダーへの入力構造体。
struct VSInput
{
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
};
//ピクセルシェーダーへの入力構造体。
struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};
///////////////////////////////////////
// PBRライティング関係の定数
///////////////////////////////////////
#include "PBRLighting_const.h"

///////////////////////////////////////
// 定数バッファ。
///////////////////////////////////////
#include "DeferredLighting_cav_register.h"

///////////////////////////////////////
// SRV_UAVのレジスタ設定
///////////////////////////////////////
#include "DeferredLighting_srv_uav_register.h"

///////////////////////////////////////
// PBRライティング
///////////////////////////////////////
#include "PBRLighting.h"

///////////////////////////////////////
// シャドウイング
///////////////////////////////////////
#include "Shadowing.h"

///////////////////////////////////////
// IBL
///////////////////////////////////////
#include "IBL.h"

///////////////////////////////////////
// 関数
///////////////////////////////////////



//頂点シェーダー。
PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

/*!
 *@brief    GIライトをサンプリング
 *@param[in]    uv              uv座標
 *@param[in]    level           映り込みレベル
 */
float4 SampleReflectionColor( float2 uv, float level )
{
    int iLevel = (int)level;
    float4 col_0;
    float4 col_1;
    if( iLevel == 0){
        col_0 = g_reflectionTextureArray[0].Sample( Sampler, uv);
        col_1 = g_reflectionTextureArray[1].Sample( Sampler, uv);
    }else if( iLevel == 1){
        col_0 = g_reflectionTextureArray[1].Sample( Sampler, uv);
        col_1 = g_reflectionTextureArray[2].Sample( Sampler, uv);
    }else if( iLevel == 2){
        col_0 = g_reflectionTextureArray[2].Sample( Sampler, uv);
        col_1 = g_reflectionTextureArray[3].Sample( Sampler, uv);
    }else if( iLevel == 3){
        col_0 = g_reflectionTextureArray[3].Sample( Sampler, uv);
        col_1 = g_reflectionTextureArray[4].Sample( Sampler, uv);
    }

    return lerp( col_0, col_1, frac(level));
}

/*!
 * @brief   UV座標と深度値からワールド座標を計算する。
 *@param[in]    uv              uv座標
 *@param[in]    zInScreen       スクリーン座標系の深度値
 *@param[in]    mViewProjInv    ビュープロジェクション行列の逆行列。
 */
float3 CalcWorldPosFromUVZ( float2 uv, float zInScreen, float4x4 mViewProjInv )
{
    float3 screenPos;
    screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2( -1.0f, 1.0f);
    screenPos.z = zInScreen;//depthMap.Sample(Sampler, uv).r;
    
    float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
    worldPos.xyz /= worldPos.w;
    return worldPos.xyz;
}
/*!
 * @brief   ディレクショナルライトの反射光を計算
 *@param[in]    normal          サーフェイスの法線。
 *@param[in]    toEye           サーフェイスから視点への方向ベクトル(単位ベクトル)
 *@param[in]    albedoColor     アルベドカラー
 *@param[in]    metaric         メタリック
 *@param[in]    smooth          滑らかさ
 *@param[in]    specColor       スペキュラカラー
 *@param[in]    worldPos        サーフェイスのワールド座標
 *@param[in]    isSoftShadow    ソフトシャドウか
 *@param[in]    shadowParam     シャドウレシーバーフラグ。
 */
float3 CalcDirectionLight(
    float3 normal, 
    float3 toEye, 
    float4 albedoColor, 
    float metaric, 
    float smooth, 
    float3 specColor,
    float3 worldPos,
    bool isSoftShadow,
    float shadowParam
){
    float3 lig = 0;
    for(int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
    {
        // ★強制的に光の向きを固定（ここを変えると光が動く）
        float3 customDir = normalize(float3(0.1f, -0.5f, -0.7f));

        // 影の比率を計算する。
        float shadow = 0.8f;
        if( light.directionalLight[ligNo].castShadow == 1){
            //影を生成する。
            shadow = CalcShadowRate( 
                g_shadowMap, 
                light.mlvp, 
                ligNo, 
                worldPos, 
                isSoftShadow ) * shadowParam;
        }
        
        float maxShadowDarkness = 0.7f; // 0.0で影が消える、1.0で真っ黒
        lig += CalcLighting(
            customDir, // ★固定した向きを適用
            light.directionalLight[ligNo].color * 1.2f,
            normal,
            toEye,
            albedoColor,
            metaric,
            smooth,
            specColor
        ) * ( 1.0f - shadow * maxShadowDarkness );
    }
    return lig;
}
/*!
 *@brief    ポイントライトの反射光を計算
 *@param[in]    normal          サーフェイスの法線。
 *@param[in]    toEye           サーフェイスから視点への方向ベクトル(単位ベクトル)
 *@param[in]    albedoColor     アルベドカラー
 *@param[in]    metaric         メタリック
 *@param[in]    smooth          滑らかさ
 *@param[in]    specColor       スペキュラカラー
 *@param[in]    worldPos        サーフェイスのワールド座標
 */
float3 CalcPointLight(
    float3 normal, 
    float3 toEye, 
    float4 albedoColor, 
    float metaric, 
    float smooth, 
    float3 specColor,
    float3 worldPos,
    float2 viewportPos
){
    float3 lig = 0;
    
    // スクリーンの左上(0,0)、右下(1,1)という座標系に変換する
    // ビューポート座標系に変換する
    // このピクセルが含まれているタイルの番号を計算する
    // スクリーンをタイルで分割したときのセルのインデックスを求める
    uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;

    // タイルインデックスを計算する
    uint tileIndex = floor(viewportPos.x / TILE_WIDTH) + floor(viewportPos.y / TILE_HEIGHT) * numCellX;

    // まずはタイルの影響ライトリストの開始位置と終了位置を計算する
    uint lightStart = tileIndex * light.numPointLight;
    uint lightEnd = lightStart + light.numPointLight;
    for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++)
    {
        uint ligNo = pointLightListInTile[lightListIndex];
        if (ligNo == 0xffffffff)
        {
            // このタイルに含まれるポイントライトはもうない
            break;
        }
        
        float3 ligDir = normalize(worldPos - light.pointLight[ligNo].position);
        // 2. 光源からサーフェイスまでの距離を計算
        float distance = length(worldPos - light.pointLight[ligNo].position);
        float3 ligColor = light.pointLight[ligNo].color;
        float3 ptLig = CalcLighting(
            ligDir,
            ligColor,
            normal,
            toEye,
            albedoColor,
            metaric,
            smooth,
            specColor
        );
        // 3. 影響度を計算する。影響度は0.0〜1.0の範囲の値。
        //    指定した距離（pointsLights[i].range）を超えたら、影響度は0.0になる
        float affect = 1.0f - min(1.0f, distance / light.pointLight[ligNo].attn.x);
        affect = pow( affect, light.pointLight[ligNo].attn.y );
        lig += ptLig * affect;
    } // ← forループはここでしっかり閉じる！

    // ========================================================
    // ★ ここから追加：力技でオリジナルのポイントライトを1個配置する！
    // ========================================================
    
    // 1. ライトを置きたい「ワールド座標(X, Y, Z)」を決める
    float3 myLightPos = float3(0.0f, 50.0f, 0.0f); 
    
    // 2. ライトの色（R, G, B）を決める（たき火や電球のような温かいオレンジ色）
    float3 myLightColor = float3(100.0f, 100.0f, 0.0f); 
    
    // 3. 光が届く「半径（距離）」を決める
    float myRange = 0.0f;

    // 4. 【重要】実際に光を計算して画面の光（lig）に足し算する処理
    float3 myLigDir = normalize(worldPos - myLightPos);
    float myDistance = length(worldPos - myLightPos);
    
    if (myDistance < myRange) {
        // PBRのライティング公式を適用して基本の光を計算
        float3 myPtLig = CalcLighting(myLigDir, myLightColor, normal, toEye, albedoColor, metaric, smooth, specColor);
        
        // 離れるほど滑らかに暗くしていく（減衰の計算）
        float myAffect = 1.0f - (myDistance / myRange);
        myAffect = pow(myAffect, 2.0f); // 2乗して減衰のボケ足を綺麗にする
        
        // 最終的な光の合計（lig）にプラスする！
        lig += myPtLig * myAffect; 
    }
    // ========================================================

    return lig;
}
/*!
 *@brief    スポットライトの反射光を計算
 *@param[in]    normal          サーフェイスの法線。
 *@param[in]    toEye           サーフェイスから視点への方向ベクトル(単位ベクトル)
 *@param[in]    albedoColor     アルベドカラー
 *@param[in]    metaric         メタリック
 *@param[in]    smooth          滑らかさ
 *@param[in]    specColor       スペキュラカラー
 *@param[in]    worldPos        サーフェイスのワールド座標
 */
float3 CalcSpotLight(
    float3 normal, 
    float3 toEye, 
    float4 albedoColor, 
    float metaric, 
    float smooth, 
    float3 specColor,
    float3 worldPos,
    float2 viewportPos
){
    float3 lig = 0;
    // スクリーンの左上(0,0)、右下(1,1)という座標系に変換する
    // ビューポート座標系に変換する

    // このピクセルが含まれているタイルの番号を計算する
    // スクリーンをタイルで分割したときのセルのインデックスを求める
    uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;

    // タイルインデックスを計算する
    uint tileIndex = floor(viewportPos.x / TILE_WIDTH) + floor(viewportPos.y / TILE_HEIGHT) * numCellX;

    // 続いてスポットライト。
    uint lightStart = tileIndex * light.numSpotLight;
    uint lightEnd = lightStart + light.numSpotLight;
    for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++)
    {
        uint ligNo = spotLightListInTile[lightListIndex];
        if (ligNo == 0xffffffff)
        {
            // このタイルに含まれるポイントライトはもうない
            break;
        }
        
        float3 ligDir = normalize(worldPos - light.spotLight[ligNo].position);
        // 2. 光源からサーフェイスまでの距離を計算
        float distance = length(worldPos - light.spotLight[ligNo].position);
        float3 ligColor = light.spotLight[ligNo].color;
        float3 ptLig = CalcLighting(
            ligDir,
            ligColor,
            normal,
            toEye,
            albedoColor,
            metaric,
            smooth,
            specColor
        );
        // 3. 影響度を計算する。影響度は0.0〜1.0の範囲の値。
        //    指定した距離を超えたら、影響度は0.0になる
        float affect = 1.0f - min(1.0f, distance / light.spotLight[ligNo].range);
        affect = pow(affect, light.spotLight[ligNo].rangePow.x);

        // 反射光と射出方向の角度による減衰を計算する
        // dot()を利用して内積を求める
        float angleLigToPixel = dot(ligDir, light.spotLight[ligNo].direction);
        // dot()で求めた値をacos()に渡して角度を求める
        angleLigToPixel = abs(acos(angleLigToPixel));
        // step-12 角度による影響度を求める
        // 角度に比例して暗くなっていく影響度を計算する
        float angleAffect = pow( max( 0.0f, 1.0f - 1.0f / light.spotLight[ligNo].angle.x * angleLigToPixel ), light.spotLight[ligNo].anglePow.x);
        affect *= angleAffect;

        lig += ptLig * affect;
    }
    return lig;
}
//ピクセルシェーダーのコア。
float4 PSMainCore(PSInput In, uniform int isSoftShadow) 
{
    //G-Bufferの内容を使ってライティング
    //アルベドカラーをサンプリング。
    float4 albedoColor = albedoTexture.Sample(Sampler, In.uv);
    //法線をサンプリング。
    float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
    //ワールド座標をサンプリング。
    float3 worldPos = CalcWorldPosFromUVZ(In.uv, albedoColor.w, light.mViewProjInv);
    //スペキュラカラーをサンプリング。
    float3 specColor = albedoColor.xyz;
    //金属度をサンプリング。
    float metaric = metallicShadowSmoothTexture.SampleLevel(Sampler, In.uv, 0).r;
    //スムース
    float smooth = metallicShadowSmoothTexture.SampleLevel(Sampler, In.uv, 0).a;

    //影用のパラメータ。
    float shadowParam = metallicShadowSmoothTexture.Sample(Sampler, In.uv).g;
    
    float2 viewportPos = In.pos.xy;

    // 視線に向かって伸びるベクトルを計算する
    float3 toEye = normalize(light.eyePos - worldPos);
    
    // ディレクショナルライトを計算
    float3 lig = CalcDirectionLight(
        normal, 
        toEye, 
        albedoColor, 
        metaric, 
        smooth, 
        specColor, 
        worldPos,
        isSoftShadow,
        shadowParam
    );
    
    lig += CalcPointLight(
        normal, 
        toEye, 
        albedoColor, 
        metaric, 
        smooth, 
        specColor, 
        worldPos,
        viewportPos
    );
    
    lig += CalcSpotLight(
        normal, 
        toEye, 
        albedoColor, 
        metaric, 
        smooth, 
        specColor, 
        worldPos,
        viewportPos
    );
    
    if(light.isEnableRaytracing){
        // レイトレーシングを行う場合のライト。本来なら鏡面反射テクスチャやIBLテクスチャからサンプリング。
        // GLテクスチャ
        float reflectionRate = 1.0f - ( ( smooth - 0.5f ) * 2.0f );
        float level = lerp(0.0f, (float)(NUM_REFLECTION_TEXTURE - 1 ), pow( reflectionRate, 3.0f ));
        if( level < NUM_REFLECTION_TEXTURE-1){
            lig += albedoColor * SampleReflectionColor(In.uv, level);
        }else if (light.isIBL == 1) {
            // IBL処理をおこなう。
            lig += albedoColor * SampleIBLColorFromSkyCube(
                g_skyCubeMap, 
                toEye, 
                normal, 
                smooth,
                light.iblIntencity
            );
        }else{
            // 環境光による底上げ（雪用のほんのり青みブレンド）
            float3 snowAmbient = light.ambientLight + float3(0.11f, 0.15f, 0.15f);
            lig += snowAmbient * albedoColor.xyz;    
        }
    }else if (light.isIBL == 1) {
        // 反射光の反射ベクトルを求める。
        lig += albedoColor * SampleIBLColorFromSkyCube(
            g_skyCubeMap, 
            toEye, 
            normal, 
            smooth,
            light.iblIntencity 
        );
    }
    else {
        // 環境光による底上げ（雪用のほんのり青みブレンド）
        float3 snowAmbient = light.ambientLight + float3(0.11f, 0.15f, 0.15f);
        lig += snowAmbient * albedoColor.xyz;
    }
   
    float4 finalColor = 1.0f;
    finalColor.xyz = lig;
    return finalColor;
}
float4 PSMainSoftShadow(PSInput In) : SV_Target0
{
    return PSMainCore( In, true);
}
//ハードシャドウを行うピクセルシェーダー。
float4 PSMainHardShadow(PSInput In) : SV_Target0
{
    return PSMainCore( In, false);
}