/********************************************************************
FluidResources.h: Contains fluid calculation resources. 
Both per-object and common resources(ones that can be shared).

Author:	Valentin Hinov
Date: 19/3/2014
*********************************************************************/

#ifndef _FLUIDRESOURCES_H
#define _FLUIDRESOURCES_H

#include <memory>
#include <array>
#include "../../display/D3DShaders/ShaderParams.h"

struct CommonFluidResources {
	ShaderParams divergenceSP;
	std::array<ShaderParams, 2>	pressureSP;
	std::array<ShaderParams, 2>	tempSP;

	static CommonFluidResources CreateResources(ID3D11Device * device, const Vector3 &textureSize, HWND hwnd);
};

struct FluidResourcesPerObject {
	std::array<ShaderParams, 2>	velocitySP;
	std::array<ShaderParams, 2>	densitySP;
	std::array<ShaderParams, 2>	temperatureSP;
	std::array<ShaderParams, 2>	reactionSP; // only used when fluid type is fire
	ShaderParams obstacleSP;
	ShaderParams vorticitySP;

	static FluidResourcesPerObject CreateResourcesSmoke(ID3D11Device * device, const Vector3 &textureSize, HWND hwnd);
	static FluidResourcesPerObject CreateResourcesFire(ID3D11Device * device, const Vector3 &textureSize, HWND hwnd);
};

#endif