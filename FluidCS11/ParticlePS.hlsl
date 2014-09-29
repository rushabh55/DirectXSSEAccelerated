struct GSParticleOut
{
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};

float4 ParticlePS(GSParticleOut In) : SV_Target
{
	return In.color;
}
