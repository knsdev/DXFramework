cbuffer VS_CBUFFER
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
};

struct VS_INPUT
{
	float3 Pos : POSITION;
	float2 UV : TEXCOORD0;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD0;
};

PS_INPUT VS_MAIN(VS_INPUT input)
{
	PS_INPUT output;
	
	output.Pos = mul(mul(mul(float4(input.Pos, 1.0f), World), View), Projection);
	output.UV = input.UV;
	
	return output;
}

