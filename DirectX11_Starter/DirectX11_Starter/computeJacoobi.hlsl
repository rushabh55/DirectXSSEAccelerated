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

Texture3D<float4>  pressure    : register (t1);
RWTexture3D<float4>  pressureRW  : register (u0);

Texture3D<float4>  divergence    : register (t0);

// jaccobi iteration to make gradient pressure equal to speed (before it has divergence 0)
[numthreads(16, 4, 4)]
//****************************************************************************
void main(uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
//****************************************************************************
{
	// early out
	if (i.x >= dim.x / 4) return;

	uint3 j;

	j = uint3(max(i.x - 1, 0), i.y, i.z);
	float4 pxm = float4(pressure[j].w, pressure[i + uint3(0, 0, 0)].xyz);
		j = uint3(min(i.x + 1, dim.x - 1), i.y, i.z);
	float4 pxp = float4(pressure[i + uint3(0, 0, 0)].yzw, pressure[j].x);

		j = uint3(i.x, max(i.y - 1, 0), i.z);
	float4 pym = pressure[j];
		j = uint3(i.x, min(i.y + 1, dim.y - 1), i.z);
	float4 pyp = pressure[j];

		j = uint3(i.x, i.y, max(i.z - 1, 0));
	float4 pzm = pressure[j];
		j = uint3(i.x, i.y, min(i.z + 1, dim.z - 1));
	float4 pzp = pressure[j];


	pressureRW[i] = (pxp + pxm + pyp + pym + pzp + pzm - divergence[i]) / 6;
}