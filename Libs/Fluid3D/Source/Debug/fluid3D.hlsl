// Coded by Jan Vlietinck, 27 Dec 2009, V 1.3
// http://users.skynet.be/fquake/


RWTexture2D<float4> output     : register (u0);

    Texture3D<float4>    speed  : register (t0);
    Texture3D<float4>   speedA  : register (t1);    
  RWTexture3D<float4>  speedRW  : register (u0);  
 
    Texture3D<float>    speedSize  : register (t0);    
  RWTexture3D<float>  speedSizeRW  : register (u1);  


    Texture3D<float4>  divergence    : register (t0);  
  RWTexture3D<float4>  divergenceRW  : register (u0);  
    
  Texture3D<float4>  pressure    : register (t1);
RWTexture3D<float4>  pressureRW  : register (u0);



SamplerState samLinear       : register( s0 );

cbuffer cbWave3D : register( b0 )
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


// advect speed, by sampling speed at 'pos - dt*speed' position
[numthreads(16, 4, 4)]
//****************************************************************************
void CS_Advect3D( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 

// advect by trace back
  float3 sam = i - speed[i];   
  sam = (sam+0.5)/dim;
  
  float4 s = speed.SampleLevel(samLinear, sam, 0);
  
  
  speedRW[i] =  s;
}


// advect speed, by sampling speed at 'pos - dt*speed' position
[numthreads(16, 4, 4)]
//****************************************************************************
void CS_AdvectBackward3D( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 
  float3 sam = i + speed[i];   
  sam = (sam+0.5)/dim;
  
  float4 s = speedA.SampleLevel(samLinear, sam, 0);
  
  speedRW[i] =  s; //speed[i] + (speed[i]-s)/2;
}

// advect speed, by sampling speed at 'pos - dt*speed' position
[numthreads(16, 4, 4)]
//****************************************************************************
void CS_AdvectMacCormack3D( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 
  
  // advect by trace back
  float3 sam = i - speed[i];   
  
  // back trace position
  uint3 j = (uint3) sam;
  
  sam = (sam+0.5)/dim;
  
  
  float4 r0 = speed[j + uint3(0,0,0)];
  float4 r1 = speed[j + uint3(1,0,0)];
  float4 r2 = speed[j + uint3(0,1,0)];
  float4 r3 = speed[j + uint3(1,1,0)];
  float4 r4 = speed[j + uint3(0,0,1)];
  float4 r5 = speed[j + uint3(1,0,1)];
  float4 r6 = speed[j + uint3(0,1,1)];
  float4 r7 = speed[j + uint3(1,1,1)];
  
  float4 lmin = min(r0,min(r1,min(r2, min(r3, min(r4, min(r5, min(r6, r7)))))));
  float4 lmax = max(r0,max(r1,max(r2, max(r3, max(r4, max(r5, max(r6, r7)))))));
  
  
  float4 s0 = speed.SampleLevel(samLinear, sam, 0);  
  
  
  
  
  float4 s =  s0 + 0.5*(s0-speedA.SampleLevel(samLinear, sam, 0));;
  //float4 s =  speedA.SampleLevel(samLinear, sam, 0);;
  
  
  // float4 s =  s0 + 0.3*(speed[i] - speedA[i]);  
  //float4 s =  speedA.SampleLevel(samLinear, sam, 0);;   
  //s = any(s.xyz > lmax.xyz) ? s0 : s;
  //s = any(s.xyz < lmin.xyz) ? s0 : s;
  

  // limit to lagrange else can be unstable, does not seem to work ok  
  s = clamp(s, lmin,lmax);
  
  
  s.w = max(s0.w - 0.001, 0);   // decrease reaction counter
    
  speedRW[i] =  s;
}


[numthreads(16, 4, 4)]
//****************************************************************************
void CS_DrawSphere( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 

  // ray shooting through mouse position
  float3 eye    = float3(0.0f, 0.0f, 4.0f);       
  float3 raydir = float3( (2*mouse.xy - float2(width, height)) / min(width, height) *zoom , 0) - eye;
  float3 viewdir  = 0                                                                          - eye;

    // calc ray volume intersection, at plane through volume origin perpendicular to view direction
  // ray = eye + t*raydir;    dot (viewdir, ray) = 0;
  
  float t = -dot(viewdir, eye) / dot(viewdir, raydir);
  
  float3 ball = eye + t*raydir;

  // rotate vuew
  ball        =  mul(              ball, rotation);
  float3 force = mul( dragDirection.xyz, rotation)*zoom*4;
  
    // calc texture coordinates of intersection
  ball  =  dim*(ball +1)/2;
  
  // calc volume coordinates relative to ball center
  ball = i - ball;
  
  float r = dot(ball, ball);  // radius^2 square
  
  // draw spere
  float g = exp( -r/(mouse.w*mouse.w));
  speedRW[i] = float4(speed[i].xyz +  force* g, speed[i].w + length(force)*g);   // put 1 in w, will serve as reaction counter    
}


// calc speed divergence, by sampling speed at 'pos - dt*speed' position
[numthreads(16, 4, 4)]
//****************************************************************************
void CS_Divergence3D( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 

  // early out
  if (i.x >= dim.x/4) return;

  float pxm, pxp, pym, pyp, pzm, pzp;
  float divergence[4];

  [unroll]
  for (int j=0; j<4; j++)
  { uint3 i4 =  uint3(4*i.x+j, i.y, i.z);
    pxm = speed[i4 + uint3(-1,0,0)].x;
    pxp = speed[i4 + uint3( 1,0,0)].x;
    pym = speed[i4 + uint3( 0,-1,0)].y;
    pyp = speed[i4 + uint3( 0, 1,0)].y;
    pzm = speed[i4 + uint3( 0,0,-1)].z;
    pzp = speed[i4 + uint3( 0,0, 1)].z;    
    divergence[j] =  (pxp - pxm + pyp - pym + pzp - pzm)/2;
  }
  divergenceRW[i] =  (float4)divergence;
  
}


// jaccobi iteration to make gradient pressure equal to speed (before it has divergence 0)
[numthreads(16, 4, 4)]
//****************************************************************************
void CS_Jaccobi3D( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 
  // early out
  if (i.x >= dim.x/4) return;
  
  uint3 j;

  j = uint3(max(i.x-1,0), i.y, i.z);
  float4 pxm = float4(pressure[j].w, pressure[i + uint3( 0,0,0)].xyz);
  j = uint3(min(i.x+1,dim.x-1), i.y, i.z);
  float4 pxp = float4(pressure[i + uint3( 0,0,0)].yzw, pressure[j].x);  
 
  j = uint3(i.x, max(i.y-1,0), i.z);
  float4 pym = pressure[j];
  j = uint3(i.x, min(i.y+1,dim.y-1), i.z);
  float4 pyp = pressure[j];
  
  j = uint3(i.x, i.y, max(i.z-1,0));
  float4 pzm = pressure[j];
  j = uint3(i.x, i.y, min(i.z+1,dim.z-1));
  float4 pzp = pressure[j];

  
  pressureRW[i] =  (pxp + pxm + pyp + pym + pzp + pzm - divergence[i])/6;
}


// make speed divergence 0. buy substracting gradient of pressure
[numthreads(16, 4, 4)]
//****************************************************************************
void CS_Project3D( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 

  // early out
  if (i.x >= dim.x/4) return;

  uint3 j;

  j = uint3(max(i.x-1,0), i.y, i.z);
  float4 pxm = float4(pressure[j].w, pressure[i + uint3( 0,0,0)].xyz);
  j = uint3(min(i.x+1,dim.x-1), i.y, i.z);
  float4 pxp = float4(pressure[i + uint3( 0,0,0)].yzw, pressure[j].x);  
 
  j = uint3(i.x, max(i.y-1,0), i.z);
  float4 pym = pressure[j];
  j = uint3(i.x, min(i.y+1,dim.y-1), i.z);
  float4 pyp = pressure[j];
  
  j = uint3(i.x, i.y, max(i.z-1,0));
  float4 pzm = pressure[j];
  j = uint3(i.x, i.y, min(i.z+1,dim.z-1));
  float4 pzp = pressure[j];
  
  pxp -=pxm;
  pyp -=pym;
  pzp -=pzm;

  float4 s;
  i.x*=4;
  bool borderyz = any(i.yz == 0 | i.yz==dim.yz-1);
  s = speed[i] - float4(pxp.x, pyp.x, pzp.x,0)/2;  
  speedRW[i] =  ( i.x == 0 || borderyz ) ? -s : s;
  speedSizeRW[i] = smoky ? s.w : length(s.xyz);
  i.x++;
  s = speed[i] - float4(pxp.y, pyp.y, pzp.y,0)/2;  
  speedRW[i] =  ( borderyz ) ? -s : s;
  speedSizeRW[i] = smoky ? s.w : length(s.xyz);
  i.x++;
  s = speed[i] - float4(pxp.z, pyp.z, pzp.z,0)/2;  
  speedRW[i] =  ( borderyz ) ? -s : s;
  speedSizeRW[i] = smoky ? s.w : length(s.xyz);
  i.x++;
  s = speed[i] - float4(pxp.w, pyp.w, pzp.w,0)/2;  
  speedRW[i] =  ( i.x == dim.x-1 || borderyz ) ? -s : s;
  speedSizeRW[i] = smoky ? s.w : length(s.xyz);

  //speedRW[i] =  speed[i] - float4(pressure[i], pyp - pym, pzp -pzm,0)/2;
}







[numthreads(16, 16, 1)]
//****************************************************************************
void CS_Render2( uint3 Gid : SV_GroupID, uint3 i : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{
  float4 color;
  
  if ( i.x < width && i.y < height)
  {
  
    float3 sam;
    sam = float3( (float) i.x / width, (float) i.y / height, (float)viewSlice/dim.z);
    sam = (viewOrientation == 1) ? float3( (float)viewSlice/dim.x, (float) i.x / width, (float) i.y / height ) : sam;
    sam = (viewOrientation == 2) ? float3( (float) i.x / width, (float)viewSlice/dim.y, (float) i.y / height ) : sam;
  
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
    float x = (float)i.x*dim.x/width -  mouse.x;
    float y = (float)i.y*dim.y/height - mouse.y;
  
    // draw blue circle   
    color =  (x*x + y*y < mouse.w*mouse.w) ? lerp(float4(1,0,1,0), color, 0.5) : color; 

  }
  else 
    color = 0;
  
  output[i.xy] = color; 
}




[numthreads(16, 16, 1)]
//****************************************************************************
void CS_Render( uint3 Gid : SV_GroupID, uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
//****************************************************************************
{ 

  float3 eye    = float3(0.0f, 0.0f, 4.0f);       
  float3 raydir = float3( (2*DTid.xy - float2(width, height)) / min(width, height) *zoom , 0) - eye;

  // rotate vuew
  eye    = mul(   eye, rotation);
  raydir = mul(raydir, rotation);

  // calc ray volume intersection, volume cube centered at origin edge size 2
  // ray = eye + t*raydir;   
  // intersect at plane x = -1 and x = 1

  float3 t1 = max((-1 - eye) / raydir, 0);
  float3 t2 = max(( 1 - eye) / raydir, 0);

  float3 front = min(t1, t2);
  float3 back  = max(t1, t2);

  float tfront = max(front.x, max(front.y, front.z));
  float tback  = min( back.x, min( back.y,  back.z));

  // calc texture coordinates of front and back intersection

  float3 texf  =  (eye + tfront*raydir + 1)/2;
  float3 texb  =  (eye + tback *raydir + 1)/2;

  float steps = floor(length(texf - texb)*dim.x+0.5);
  float3 texdir = (texb-texf)/steps;
  

  steps = (tfront >= tback) ? 0 : steps; // no intersection ?
  // simple MIP render
  float m = 0;
  for (float i=0.5; i< steps; i++)
  {
    float3 sam = texf + i*texdir;
    float s = speedSize.SampleLevel(samLinear, sam, 0);      
    m = max(m, s);     
  }

  // hot metal color
  float4 col = saturate(lerp(float4(0,-1.41,-3, -0.4), float4(1.41,1.41,1, 1.41), m/3));		 

  
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



