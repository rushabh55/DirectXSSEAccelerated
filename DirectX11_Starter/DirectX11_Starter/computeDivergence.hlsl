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

Texture3D<float4>  divergence    : register (t0);
RWTexture3D<float4>  divergenceRW  : register (u0);
//
// calc speed divergence, by sampling speed at 'pos - dt*speed' position
[numthreads(16, 4, 4)]
//****************************************************************************
void main(uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
//****************************************************************************
{
	// early out
	if (i.x >= dim.x / 4) return;

	float pxm, pxp, pym, pyp, pzm, pzp;
	float divergence[4];

	[unroll]
	for (int j = 0; j<4; j++)
	{
		uint3 i4 = uint3(4 * i.x + j, i.y, i.z);
			pxm = speed[i4 + uint3(-1, 0, 0)].x;
		pxp = speed[i4 + uint3(1, 0, 0)].x;
		pym = speed[i4 + uint3(0, -1, 0)].y;
		pyp = speed[i4 + uint3(0, 1, 0)].y;
		pzm = speed[i4 + uint3(0, 0, -1)].z;
		pzp = speed[i4 + uint3(0, 0, 1)].z;
		divergence[j] = (pxp - pxm + pyp - pym + pzp - pzm) / 2;
	}
	divergenceRW[i] = (float4)divergence;
}