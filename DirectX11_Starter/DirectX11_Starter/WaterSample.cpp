#pragma once

#include "WaterSample.h"
#include "DXGame.h"
#include "dxerr.h"

using namespace DirectX;
using namespace std;

const u8 viewSlice = 200 / 2;
const f32 zoom = 1.2;
const Bool smoky = true;

const i16 DimX = DIMXYZ;
const i16 DimY = DIMXYZ;
const i16 DimZ = DIMXYZ;

WaterSample::WaterSample(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	this->device = device;
	this->deviceContext = deviceContext;
}

void WaterSample::SetMousePosition(float x, float y)
{
	mousePosXPrev = mousePosX;
	mousePosYPrev = mousePosY;
	mousePosX = x;
	mousePosY = y;
}

void WaterSample::Initialize()
{
	
	// Create compute shader
	DWORD dwShaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3D10_SHADER_DEBUG;
#endif

	HRESULT hr;
	{
		ID3DBlob* csBlob;

		//Comput Advect;
		D3DReadFileToBlob(L"computeAdvect.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSAdvect3D));
		ReleaseMacro(csBlob);

		D3DReadFileToBlob(L"computeAdvectBack.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSAdvectBackward3D));
		ReleaseMacro(csBlob);

		D3DReadFileToBlob(L"computeCormack.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSMacCormack3D));
		ReleaseMacro(csBlob);
		
		D3DReadFileToBlob(L"computeDivergence.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSDivergence3D));
		ReleaseMacro(csBlob);

		D3DReadFileToBlob(L"computeJacoobi.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSJaccobi3D));
		ReleaseMacro(csBlob);

		D3DReadFileToBlob(L"computeProject.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSProject3D));
		ReleaseMacro(csBlob);

		D3DReadFileToBlob(L"sphereRenderer.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSDrawSphere));
		ReleaseMacro(csBlob);
		
		D3DReadFileToBlob(L"computeRenderer.cso", &csBlob);
		HR(device->CreateComputeShader((DWORD*)csBlob->GetBufferPointer(), csBlob->GetBufferSize(), NULL, &g_pCSRender));
		ReleaseMacro(csBlob);
	}

	CreateVolumes();



	// Create constant buffer
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.ByteWidth = ((sizeof(Wave3DConstants) + 15) / 16) * 16; // must be multiple of 16 bytes
	device->CreateBuffer(&Desc, NULL, &g_pcbWave3D);



	// Create sampler state 
	D3D11_SAMPLER_DESC SSDesc;
	ZeroMemory(&SSDesc, sizeof(D3D11_SAMPLER_DESC));
	SSDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SSDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;   // zero speed at border
	SSDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	SSDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	SSDesc.BorderColor[0] = 0;
	SSDesc.BorderColor[1] = 0;
	SSDesc.BorderColor[2] = 0;
	SSDesc.BorderColor[3] = 0;
	SSDesc.MipLODBias = 0;
	SSDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SSDesc.MaxAnisotropy = 16;
	SSDesc.MinLOD = 0;
	SSDesc.MaxLOD = D3D11_FLOAT32_MAX;
	device->CreateSamplerState(&SSDesc, &g_pSamplerStateLinear);

	// set CS sampler
	deviceContext->CSSetSamplers(0, 1, &g_pSamplerStateLinear);


}

void WaterSample::UpdateShaders()
{
#pragma region Setting Constant Buffers
	D3D11_MAPPED_SUBRESOURCE msr;
	deviceContext->Map(g_pcbWave3D, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	Wave3DConstants mc;

	mc.dim[0] = DimX;
	mc.dim[1] = DimY;
	mc.dim[2] = DimZ;

	mc.width = 0;
	mc.height = 0;

	mc.viewSlice = 100;
	mc.viewOrientation = 0;

	mc.mouse[0] = (float)mousePosX; //  *DimX / g_width;
	mc.mouse[1] = (float)mousePosY; // * DimY / g_height;
	mc.mouse[2] = viewSlice;
	mc.mouse[3] = 3; // radius in voxels;

	if (drag)
	{
		mc.dragDirection[0] = (float)(mousePosX - mousePosXPrev)*DimX / 800;
		mc.dragDirection[1] = (float)(mousePosY - mousePosYPrev)*DimY / 600;
	}
	else
	{
		mc.dragDirection[0] = 0;
		mc.dragDirection[1] = 0;
	}
	mc.dragDirection[2] = 0;

	mc.zoom = zoom;
	mc.smoky = smoky;

	*(Wave3DConstants * )msr.pData = mc;
	deviceContext->Unmap(g_pcbWave3D, 0);

	ID3D11Buffer* ppCB[1] = { g_pcbWave3D };
	deviceContext->CSGetConstantBuffers(0, 1, ppCB);
#pragma endregion 

#pragma region RunShaders
	RunComputeShader(g_pCSAdvect3D, pSpeed[0], { NULL, NULL }, pSpeed[1], { NULL, NULL }, (DimX + 15) / 16, DimY / 4, DimZ / 4);
	RunComputeShader(g_pCSAdvectBackward3D, pSpeed[0], pSpeed[1], pSpeed[2], { NULL, NULL }, (DimX + 15) / 16, DimY / 4, DimZ / 4);

	//  second order correction
	RunComputeShader(g_pCSMacCormack3D, pSpeed[0], pSpeed[2], pSpeed[1], { NULL, NULL }, (DimX + 15) / 16, DimY / 4, DimZ / 4);
	RunComputeShader(g_pCSDrawSphere, pSpeed[1], { NULL, NULL }, pSpeed[0], { NULL, NULL }, (DimX + 15) / 16, DimY / 4, DimZ / 4);

	// calc speed divergence
	RunComputeShader(g_pCSDivergence3D, pSpeed[0], { NULL, NULL }, pDivergence, { NULL, NULL }, (DimX + 63) / 64, DimY / 4, DimZ / 4);
	for (int i = 0; i<10; i++)
	{
		RunComputeShader(g_pCSJaccobi3D, pDivergence, pPressure[1], pPressure[0], NULLres, (DimX + 63) / 64, DimY / 4, DimZ / 4);
		RunComputeShader(g_pCSJaccobi3D, pDivergence, pPressure[0], pPressure[1], NULLres, (DimX + 63) / 64, DimY / 4, DimZ / 4);
	}

	// project
	RunComputeShader(g_pCSProject3D, pSpeed[0], pPressure[1], pSpeed[1], pSpeedSize, (DimX + 63) / 64, DimY / 4, DimZ / 4);


	// render output
	RunComputeShader(g_pCSRender, pSpeedSize, pPressure[1], pRenderOutput, NULLres, (SCR_WIDTH + 15) / 16, (SCR_HEIGHT + 15) / 16, 1);


#pragma endregion
}

void WaterSample::UnbindShaders()
{
	ID3D11ShaderResourceView* aSRiews[] = { NULL, NULL };
	deviceContext->CSSetShaderResources(0, 2, aSRiews);

	ID3D11UnorderedAccessView* aUAViews[] = { NULL, NULL };
	deviceContext->CSSetUnorderedAccessViews(0, 2, aUAViews, (UINT*)(&aUAViews));
}

void WaterSample::RunComputeShader(ID3D11ComputeShader* shader, Resource in0, Resource in1, Resource out0, Resource out1, int dx, int dy, int dz)
{
	//Set Shader Resource views
	ID3D11ShaderResourceView* aSRiews[] = { in0.srv, in1.srv };
	deviceContext->CSSetShaderResources(0, 2, aSRiews);

	// Set unordered access views for writees
	ID3D11UnorderedAccessView* aUAViews[] = { out0.uav, out1.uav };
	deviceContext->CSSetUnorderedAccessViews(0, 2, aUAViews, (UINT*)(&aUAViews));

	// Set compute shader
	deviceContext->CSSetShader(shader, NULL, 0);

	// Run compute shader
	deviceContext->Dispatch(dx, dy, dz);

	UnbindShaders();
}

void WaterSample::CreateVolumes()
{
	unsigned short  *volume = new  unsigned short[DimX*DimY*DimZ * 4];

	memset(volume, 0, DimX*DimY*DimZ * 2 * 4);

	D3D11_TEXTURE3D_DESC desc;
	desc.Width = DimX;
	desc.Height = DimY;
	desc.Depth = DimZ;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	desc.Usage = D3D11_USAGE_DEFAULT;    // D3D11_USAGE_STAGING  for mapping + copy cpu to gpu
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	desc.CPUAccessFlags = 0;  // D3D11_CPU_ACCESS_WRITE  or D3D11_CPU_ACCESS_READ for mapping
	desc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = volume;
	data.SysMemPitch = DimX * 4 * 2;
	data.SysMemSlicePitch = DimX*DimY * 4 * 2;


	for (int i = 0; i<3; i++)
	{
		device->CreateTexture3D(&desc, &data, &pSpeedTex[i]);
		device->CreateUnorderedAccessView(pSpeedTex[i], NULL, &pSpeed[i].uav);
		device->CreateShaderResourceView(pSpeedTex[i], NULL, &pSpeed[i].srv);
	}



	// half format  s eeeee  mmmmmmmmmm
	//  s : sign bit of float
	//  eeeee : exponent range [-15 15], stored as unsigned exponent + 15
	//  mmmmmmmmm : mantisse


	// Pressure
	desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	desc.Width = DimX / 4;

	data.SysMemPitch = DimX * 2;
	data.SysMemSlicePitch = DimX*DimY * 2;

	for (int i = 0; i<2; i++)
	{
		// create grow volume
		device->CreateTexture3D(&desc, &data, &pPressureTex[i]);
		device->CreateUnorderedAccessView(pPressureTex[i], NULL, &pPressure[i].uav);
		device->CreateShaderResourceView(pPressureTex[i], NULL, &pPressure[i].srv);
	}

	// Divergence
	device->CreateTexture3D(&desc, &data, &pDivergenceTex);
	device->CreateUnorderedAccessView(pDivergenceTex, NULL, &pDivergence.uav);
	device->CreateShaderResourceView(pDivergenceTex, NULL, &pDivergence.srv);


	// speed size (length velocity vector)
	desc.Format = DXGI_FORMAT_R16_FLOAT;
	desc.Width = DimX;
	device->CreateTexture3D(&desc, NULL, &pSpeedSizeTex);
	device->CreateUnorderedAccessView(pSpeedSizeTex, NULL, &pSpeedSize.uav);
	device->CreateShaderResourceView(pSpeedSizeTex, NULL, &pSpeedSize.srv);


	delete[] volume;


	// temp 2d slice in for to vector to scalar conversion

	D3D11_TEXTURE2D_DESC desc2;
	desc2.Width = DimX;
	desc2.Height = DimY;
	desc2.MipLevels = 1;
	desc2.ArraySize = 1;
	desc2.SampleDesc.Count = 1;
	desc2.SampleDesc.Quality = 0;
	desc2.Format = DXGI_FORMAT_R16_FLOAT;
	desc2.Usage = D3D11_USAGE_DEFAULT;    // D3D11_USAGE_STAGING  for mapping + copy cpu to gpu
	desc2.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	desc2.CPUAccessFlags = 0;  // D3D11_CPU_ACCESS_WRITE  or D3D11_CPU_ACCESS_READ for mapping
	desc2.MiscFlags = 0;
	device->CreateTexture2D(&desc2, NULL, &pSliceTex);
	device->CreateUnorderedAccessView(pSliceTex, NULL, &pSliceUAV);
	device->CreateShaderResourceView(pSliceTex, NULL, &pSliceSRV);
}