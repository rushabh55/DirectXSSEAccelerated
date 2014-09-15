
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

RWTexture2D<float4> output     : register (u0);

Texture3D<float>    speedSize  : register (t0);
SamplerState samLinear       : register(s0);

[numthreads(16, 16, 1)]
//****************************************************************************
void CS_Render2(uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
//****************************************************************************
{
	float4 color;

	if (i.x < width && i.y < height)
	{

		float3 sam;
		sam = float3((float)i.x / width, (float)i.y / height, (float)viewSlice / dim.z);
		sam = (viewOrientation == 1) ? float3((float)viewSlice / dim.x, (float)i.x / width, (float)i.y / height) : sam;
		sam = (viewOrientation == 2) ? float3((float)i.x / width, (float)viewSlice / dim.y, (float)i.y / height) : sam;

		float3 s = speed.SampleLevel(samLinear, sam, 0);
			color = length(s);

		// hot metal color
		//color = saturate(lerp(float4(0,-1.41,-3,0), float4(1.41,1.41,1,0), length(s)/3));		 

		//color = speed.SampleLevel(samLinear, sam, 0).w/5; //length(s);  

		/*
		float t = speed.SampleLevel(samLinear, sam, 0).w; //length(s);
		float c =  t*2*3.1416f/10;  // color cycle
		color.r = (1+cos(  c)              )/2;
		color.g = (1+cos(2*c + 2*3.1416f/3))/2;
		color.b = (1+cos(  c - 2*3.1416f/3))/2;
		color.a = 1;

		color = (t==0) ? 0 : color;
		*/

		//color = abs(pressure.SampleLevel(samLinear, sam, 0));

		//color = abs(divergence.SampleLevel(samLinear, sam, 0))*10;



		// overdraw pressure in blue
		//color = abs(pressure.SampleLevel(samLinear, sam, 0));    
		// color =  (q > 0) ? lerp(float4(0,0,1,0), color, 0.5) : color; 


		// draw mouse boall
		float x = (float)i.x*dim.x / width - mouse.x;
		float y = (float)i.y*dim.y / height - mouse.y;

		// draw blue circle   
		color = (x*x + y*y < mouse.w*mouse.w) ? lerp(float4(1, 0, 1, 0), color, 0.5) : color;

	}
	else
		color = 0;

	output[i.xy] = color;
}




[numthreads(16, 16, 1)]
//****************************************************************************
void main(uint3 Gid : SV_GroupID, uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)
//****************************************************************************
{

	float3 eye = float3(0.0f, 0.0f, 4.0f);
		float3 raydir = float3((2 * DTid.xy - float2(width, height)) / min(width, height) *zoom, 0) - eye;

		// rotate vuew
		eye = mul(eye, rotation);
	raydir = mul(raydir, rotation);

	// calc ray volume intersection, volume cube centered at origin edge size 2
	// ray = eye + t*raydir;   
	// intersect at plane x = -1 and x = 1

	float3 t1 = max((-1 - eye) / raydir, 0);
		float3 t2 = max((1 - eye) / raydir, 0);

		float3 front = min(t1, t2);
		float3 back = max(t1, t2);

		float tfront = max(front.x, max(front.y, front.z));
	float tback = min(back.x, min(back.y, back.z));

	// calc texture coordinates of front and back intersection

	float3 texf = (eye + tfront*raydir + 1) / 2;
		float3 texb = (eye + tback *raydir + 1) / 2;

		float steps = floor(length(texf - texb)*dim.x + 0.5);
	float3 texdir = (texb - texf) / steps;


		steps = (tfront >= tback) ? 0 : steps; // no intersection ?
	// simple MIP render
	float m = 0;
	for (float i = 0.5; i< steps; i++)
	{
		float3 sam = texf + i*texdir;
			float s = speedSize.SampleLevel(samLinear, sam, 0);
		m = max(m, s);
	}

	// hot metal color
	float4 col = saturate(lerp(float4(0, -1.41, -3, -0.4), float4(1.41, 1.41, 1, 1.41), m / 3));


		/*
		float4 col = 0;
		for (float i=0.5; i< steps; i++)
		{
		float3 sam = texf + i*texdir;
		float s = speedSize.SampleLevel(samLinear, sam, 0);
		float4 c = saturate(lerp(float4(0,-1.41,-3, -0.4), float4(1.41,1.41,1, 1.41), s/3));

		col.rgb += c.rgb *c.a*(1-col.a);
		col.a   +=        c.a*(1-col.a);
		}
		*/


		output[DTid.xy] = col;
}
