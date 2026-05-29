/*!
 * @brief	�V���v���ȃ��f���V�F�[�_�[�B
 */


////////////////////////////////////////////////
// �\����
////////////////////////////////////////////////

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
	float4 pos : SV_POSITION; //���W�B
	float3 normal : NORMAL; //�@���B
	float3 tangent : TANGENT; //�ڃx�N�g���B
	float3 biNormal : BINORMAL; //�]�x�N�g���B
	float2 uv : TEXCOORD0; //UV���W�B
	float3 worldPos : TEXCOORD1; // ���[���h���W
};


///////////////////////////////////////
// ���_�V�F�[�_�[�̋��ʏ������C���N���[�h����B
///////////////////////////////////////
#include "ModelVSCommon.h"

///////////////////////////////////////
// PBR���C�e�B���O�֌W�̒萔
///////////////////////////////////////
#include "PBRLighting_const.h"

///////////////////////////////////////
// �V�F�[�_�[���\�[�X
///////////////////////////////////////
#include "model_srv_uav_register.h"

///////////////////////////////////////
// PBR���C�e�B���O
///////////////////////////////////////
#include "PBRLighting.h"

///////////////////////////////////////
// �V���h�E�C���O
///////////////////////////////////////
#include "Shadowing.h"

///////////////////////////////////////
// IBL
///////////////////////////////////////
#include "IBL.h"

////////////////////////////////////////////////
// �֐���`�B
////////////////////////////////////////////////

// ���f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer)
{
	SPSIn psIn;
    
    // ���_���W�����[���h���W�n�ɕϊ�����B
    psIn.pos = CalcVertexPositionInWorldSpace(vsIn.pos, mWorldLocal, isUsePreComputedVertexBuffer);

    // ���_�V�F�[�_�[���烏�[���h���W���o��
	psIn.worldPos = psIn.pos;

	psIn.pos = mul(mView, psIn.pos); // ���[���h���W�n����J�������W�n�ɕϊ�
	psIn.pos = mul(mProj, psIn.pos); // �J�������W�n����X�N���[�����W�n�ɕϊ�
    
	// ���[���h��Ԃ̖@���A�ڃx�N�g���A�]�x�N�g�����v�Z����B
	CalcVertexNormalTangentBiNormalInWorldSpace(
		psIn.normal,
		psIn.tangent,
		psIn.biNormal,
		mWorldLocal,
		vsIn.normal,
		vsIn.tangent,
		vsIn.biNormal,
		isUsePreComputedVertexBuffer
	);

	psIn.uv = vsIn.uv;
	
	return psIn;
}
/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
float4 PSMainCore( SPSIn In, uniform int isSoftShadow ) 
{
	//G-Buffer�̓��e���g���ă��C�e�B���O
    //�A���x�h�J���[���T���v�����O�B
    float4 albedoColor = albedoTexture.Sample(Sampler, In.uv);
    //�@�����T���v�����O�B
    // 1. テクスチャから法線をサンプリング (0.0 ～ 1.0)
    float3 texNormal = normalTexture.Sample(Sampler, In.uv).xyz;

    // 2. 範囲を -1.0 ～ 1.0 に展開
    float3 normalData = texNormal * 2.0f - 1.0f;

    // ★ここで強度を調整！ (0.0 で完全に真っ平ら、1.0 で元の強さ)
    // 雪が汚く見えるときは、ここを 0.1 ～ 0.3 あたりに下げてみて
    float normalStrength = 9999.0f; 
    normalData.x *= normalStrength;
    normalData.y *= normalStrength;

    // 3. 傾きを調整した法線を、モデルの表面の向き（接空間 -> ワールド空間）に変換する
    // このシェーダーには In.tangent や In.biNormal が用意されているので、それを使います
    float3x3 matTBN = float3x3(normalize(In.tangent), normalize(In.biNormal), normalize(In.normal));
    float3 normal = normalize(mul(normalData, matTBN));
    //���[���h���W���T���v�����O�B
    float3 worldPos = In.worldPos;
    //�X�y�L�����J���[���T���v�����O�B
    float3 specColor = albedoColor.xyz;
    //�����x���T���v�����O�B
    float metaric = metallicShadowSmoothTexture.SampleLevel(Sampler, In.uv, 0).r;
    //�X���[�X
    float smooth = metallicShadowSmoothTexture.SampleLevel(Sampler, In.uv, 0).a;

    //�e�����p�̃p�����[�^�B
    float shadowParam = 1.0f;
    
    float2 viewportPos = In.pos.xy;

	 // �����Ɍ������ĐL�т�x�N�g�����v�Z����
    float3 toEye = normalize(light.eyePos - worldPos);

    float3 lig = 0;
    
    for(int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
    {
        // �e�̗�������v�Z����B
        float shadow = 0.0f;
        if( light.directionalLight[ligNo].castShadow == 1){
            //�e�𐶐�����Ȃ�B
            shadow = CalcShadowRate( g_shadowMap, light.mlvp, ligNo, worldPos, isSoftShadow ) * shadowParam;
        }
        
        lig += CalcLighting(
            light.directionalLight[ligNo].direction,
            light.directionalLight[ligNo].color,
            normal,
            toEye,
            albedoColor,
            metaric,
            smooth,
            specColor
        ) * ( 1.0f - shadow * 0.2f);
    }
	
	 if (light.isIBL == 1) {
        // ��������̔��˃x�N�g�������߂�B
        lig += albedoColor * SampleIBLColorFromSkyCube(
            g_skyCubeMap,
            toEye,
            normal,
            smooth,
            light.iblIntencity
        );
    }
    else {
        // �����ɂ���グ
        lig += light.ambientLight * albedoColor;
    }
   
	float4 finalColor = 1.0f;
    finalColor.xyz = lig;
    return float4(finalColor.xyz, albedoColor.a);
}
float4 PSMainSoftShadow(SPSIn In) : SV_Target0
{
    return PSMainCore( In, true);
}
//�n�[�h�V���h�E���s���s�N�Z���V�F�[�_�[�B
float4 PSMainHardShadow(SPSIn In) : SV_Target0
{
    return PSMainCore( In, false);
} 