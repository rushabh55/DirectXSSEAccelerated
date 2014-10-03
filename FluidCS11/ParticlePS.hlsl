struct GSParticleOut
{
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};

Texture2D myTexture : register(t3);
SamplerState mySampler	: register(s0);


float4 ParticlePS(GSParticleOut In) : SV_Target
{
	float3 tmp = myTexture.Sample(mySampler, In.texcoord).xyz;
	float4 output = float4(tmp, 1);
	return normalize ( output );
//	return In.color;
}
