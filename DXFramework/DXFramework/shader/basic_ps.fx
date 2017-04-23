Texture2D g_MeshTexture;

SamplerState MeshTextureSampler;

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD0;
};

float4 PS_MAIN(PS_INPUT input) : SV_TARGET
{
	float4 output;

	output = g_MeshTexture.Sample(MeshTextureSampler, input.UV);

	return output;
}

