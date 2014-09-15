#pragma once
#include <Core/BasicTypes.h>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using namespace DirectX;
using namespace std;

#define DIMXYZ 200

int DimX = DIMXYZ;
int DimY = DIMXYZ;
int DimZ = DIMXYZ;

class WaterSample
{
public:
	explicit	WaterSample(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Initialize();
	void Update(float mouseX, float mouseY);
	void LoadShaders();
	void UpdateShaders();
	void Render();

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


	ID3D11Buffer*		    				g_pcbWave3D;       // constant buffer

	ID3D11SamplerState*         g_pSamplerStateLinear;

	// render output
	Resource                 pRenderOutput;


private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
};