#pragma once
#include <Core/BasicTypes.h>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using namespace DirectX;
using namespace std;

#define DIMXYZ 200
#define NULLres { NULL, NULL }
#define SCR_WIDTH 800
#define SCR_HEIGHT 600



class WaterSample
{
public:
	explicit	WaterSample(ID3D11Device* device, ID3D11DeviceContext* deviceContext, IDXGISwapChain* g_pSwapChain);
	void Initialize();
	void UpdateShaders();
	void SetMousePosition(float x, float y);

	typedef struct Resource
	{
		ID3D11ShaderResourceView*  srv;
		ID3D11UnorderedAccessView* uav;
	}   __declspec (align(16));

	typedef struct Wave3DConstants
	{
		float dim[4];   // size of volume

		int width;  // size viewport
		int height;
		int viewSlice;  // slice of volume to render
		int viewOrientation; // 0,1,2  for xy slice, yz sice, xz slice

		float mouse[4];
		float dragDirection[4];

		float orientation[4 * 4]; // rotation matrix

		float zoom;
		int   smoky; // toggle between fire or smoky simulation

	} __declspec ( align(16) );

protected:
	ID3D11ComputeShader*        g_pCSDrawSphere;
	ID3D11ComputeShader*        g_pCSAdvect3D;
	ID3D11ComputeShader*        g_pCSAdvectBackward3D;
	ID3D11ComputeShader*        g_pCSMacCormack3D;
	ID3D11ComputeShader*        g_pCSDivergence3D;
	ID3D11ComputeShader*        g_pCSJaccobi3D;
	ID3D11ComputeShader*        g_pCSProject3D;


	ID3D11ComputeShader*        g_pCSRender;
	ID3D11ComputeShader*        g_pCSVectorToScalar;

	ID3D11Buffer*		    				g_pcbWave3D;       // constant buffer

	ID3D11SamplerState*         g_pSamplerStateLinear;

	// render output
	Resource                 pRenderOutput;

	// Speed
	ID3D11Texture3D*          pSpeedTex[3];
	Resource pSpeed[3];

	ID3D11Texture3D*          pSpeedSizeTex;
	Resource pSpeedSize;
	// Divergence
	ID3D11Texture3D*          pDivergenceTex;
	Resource pDivergence;

	// Pressure
	ID3D11Texture3D*          pPressureTex[2];
	Resource pPressure[2];

	void UnbindShaders();
	void RunComputeShader(ID3D11ComputeShader* shader, Resource in0, Resource in1, Resource out0, Resource out1, int dx, int dy, int dz);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	f32 mousePosX;
	f32 mousePosY;
	f32 mousePosXPrev;
	f32 mousePosYPrev;
	Bool drag;
	void CreateVolumes();

	// temp 2d slice for vector to scalar conversion
	ID3D11Texture2D*           pSliceTex;
	ID3D11UnorderedAccessView* pSliceUAV;
	ID3D11ShaderResourceView*  pSliceSRV;
	IDXGISwapChain*            g_pSwapChain;
};