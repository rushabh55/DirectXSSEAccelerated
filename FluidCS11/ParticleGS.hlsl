
struct VSParticleOut
{
	float2 position : POSITION;
	float4 color : COLOR;
};

struct GSParticleOut
{
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};

struct Particle
{
	float4 VARS;
};


cbuffer cbRenderConstants : register(b0)
{
	matrix g_mViewProjection;
	float g_fParticleSize;
};



struct ParticleDensity
{
	float density;
};


struct FOO
{
	float4 color;
};
StructuredBuffer<Particle> ParticlesRO					: register(t0);
StructuredBuffer<ParticleDensity> ParticleDensityRO		: register(t1);
StructuredBuffer<FOO> ParticleColor						: register(t2);




static const float2 g_positions[4] = { float2(-1, 1), float2(1, 1), float2(-1, -1), float2(1, -1) };
static const float2 g_texcoords[4] = { float2(0, 1), float2(1, 1), float2(0, 0), float2(1, 0) };

[maxvertexcount(4)]
void ParticleGS(point VSParticleOut In[1], inout TriangleStream<GSParticleOut> SpriteStream)
{
	[unroll]
	for (int i = 0; i < 4; i++)
	{
		GSParticleOut Out = (GSParticleOut)0;
		float4 position = float4(In[0].position, 0, 1) + g_fParticleSize * float4(g_positions[i], 0, 0);
			Out.position = mul(position, g_mViewProjection);
		Out.color = ParticleColor[i].color ? ParticleColor[i].color : float4(0, 0, 0, 1);
		Out.texcoord = g_texcoords[i];
		SpriteStream.Append(Out);
	}
	SpriteStream.RestartStrip();
}
