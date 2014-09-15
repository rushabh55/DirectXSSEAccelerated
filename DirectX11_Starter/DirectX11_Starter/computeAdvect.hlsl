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
SamplerState samLinear       : register(s0);

[numthreads(16, 4, 4)]
void main( uint3 DTid : SV_DispatchThreadID, uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
{
	// advect by trace back
	float3 sam = DTid - speed[DTid];
		sam = (sam + 0.5) / dim;

	float4 s = speed.SampleLevel(samLinear, sam, 0);

	speedRW[DTid] = s;
}

