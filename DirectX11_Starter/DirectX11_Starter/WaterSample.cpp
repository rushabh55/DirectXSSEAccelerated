#pragma once

#include "WaterSample.h"

using namespace DirectX;
using namespace std;

WaterSample::WaterSample(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	this->device = device;
	this->deviceContext = deviceContext;
}

void WaterSample::Initialize()
{
	
}

void WaterSample::UpdateShaders()
{
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
}