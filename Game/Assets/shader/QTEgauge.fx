cbuffer cb : register(b0){
	float4x4 mvp;		
	float4 mulColor;	
};

cbuffer GaugeCB : register(b1)
{
    float gaugeRate;
};

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
    float2 uv = In.uv;

    float2 center = float2(0.5, 0.5);

    float2 dir = uv - center;

    float angle = atan2(dir.y, dir.x);

	angle += 1.570796f;


    if (angle < 0)
    {
        angle += 6.283185f;
    }

    float gaugeAngle = gaugeRate * 6.283185f;

    if (angle > gaugeAngle)
    {
        discard;
    }

    return colorTexture.Sample(Sampler, uv) * mulColor;
}
float4 PSMainGamma( PSInput In ) : SV_Target0
{
	float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	color.xyz =  pow(max( color.xyz, 0.0001f ), 1.0f/2.2f);
	return color;
}