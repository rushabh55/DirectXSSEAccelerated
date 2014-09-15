//TODO:: Needs work
cbuffer cbWave3D : register(b0)
{
	float4 dim;  // size of volume

	uint width;  // size viewport
	uint height;

	uint viewSlice;  // slice of volume to render
	uint viewOrientation; // 0,1,2  for xy slice, yz sice, xz slice

	float4 mouse;
	float4 dragDirection;

	float4x4 rotation;
	float zoom;
	int   smoky;  // toggle between fire or smoky simuliation
};

Texture3D<float4>    speed  : register (t0);
RWTexture3D<float4>  speedRW  : register (u0);

Texture3D<float4>   speedA  : register (t1);
SamplerState samLinear       : register(s0);

[numthreads( 16, 4, 4 )]
void main(uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
//****************************************************************************
{

	// advect by trace back
	float3 sam = i - speed[i];

		// back trace position
		uint3 j = (uint3) sam;

		sam = (sam + 0.5) / dim;


	float4 r0 = speed[j + uint3(0, 0, 0)];
		float4 r1 = speed[j + uint3(1, 0, 0)];
		float4 r2 = speed[j + uint3(0, 1, 0)];
		float4 r3 = speed[j + uint3(1, 1, 0)];
		float4 r4 = speed[j + uint3(0, 0, 1)];
		float4 r5 = speed[j + uint3(1, 0, 1)];
		float4 r6 = speed[j + uint3(0, 1, 1)];
		float4 r7 = speed[j + uint3(1, 1, 1)];

		float4 lmin = min(r0, min(r1, min(r2, min(r3, min(r4, min(r5, min(r6, r7)))))));
		float4 lmax = max(r0, max(r1, max(r2, max(r3, max(r4, max(r5, max(r6, r7)))))));


		float4 s0 = speed.SampleLevel(samLinear, sam, 0);
		float4 s = s0 + 0.5*(s0 - speedA.SampleLevel(samLinear, sam, 0));;
		s = clamp(s, lmin, lmax);


	s.w = max(s0.w - 0.001, 0);   // decrease reaction counter

	speedRW[i] = s;
}
