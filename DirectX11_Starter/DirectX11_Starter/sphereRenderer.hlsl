
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
RWTexture3D<float4>  speedRW  : register (u0);
Texture3D<float4>    speed  : register (t0);

[numthreads(16, 4, 4)]
//****************************************************************************
void main(uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
//****************************************************************************
{

	// ray shooting through mouse position
	float3 eye = float3(0.0f, 0.0f, 4.0f);
		float3 raydir = float3((2 * mouse.xy - float2(width, height)) / min(width, height) *zoom, 0) - eye;
		float3 viewdir = 0 - eye;

		// calc ray volume intersection, at plane through volume origin perpendicular to view direction
		// ray = eye + t*raydir;    dot (viewdir, ray) = 0;

		float t = -dot(viewdir, eye) / dot(viewdir, raydir);

	float3 ball = eye + t*raydir;

		// rotate vuew
		ball = mul(ball, rotation);
	float3 force = mul(dragDirection.xyz, rotation)*zoom * 4;

		// calc texture coordinates of intersection
		ball = dim*(ball + 1) / 2;

	// calc volume coordinates relative to ball center
	ball = i - ball;

	float r = dot(ball, ball);  // radius^2 square

	// draw spere
	float g = exp(-r / (mouse.w*mouse.w));
	speedRW[i] = float4(speed[i].xyz + force* g, speed[i].w + length(force)*g);   // put 1 in w, will serve as reaction counter    
}
