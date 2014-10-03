struct VSParticleOut
{
	float2 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD; //added
};

struct Particle
{
	float4 VARS;
};
struct FOO
{
	float4 color;
};

StructuredBuffer<Particle> ParticlesRO : register(t0);
StructuredBuffer<FOO> ParticleColor : register(t2);

float4 VisualizeNumber(uint n)
{
	return ParticleColor[n].color;
}

VSParticleOut ParticleVS(uint ID : SV_VertexID, VSParticleOut ot)
{
	VSParticleOut Out;
	Out.position = ParticlesRO[ID].VARS.xy;
	Out.uv.x = 0.0f;
	Out.uv.y = 1.0f;
	Out.color = VisualizeNumber(ID);
	return Out;
}