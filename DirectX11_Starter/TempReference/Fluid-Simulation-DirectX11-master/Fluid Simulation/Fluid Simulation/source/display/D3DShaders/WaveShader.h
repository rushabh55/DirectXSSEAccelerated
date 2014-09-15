/*************************************************************
WaveShader.h: Describes a shader that solves the 2D wave
equation

Author: Valentin Hinov
Date: 06/09/2013
Version: 1.0
**************************************************************/
#ifndef _WAVESHADER_H
#define _WAVESHADER_H

#include "BaseD3DShader.h"

class D3DGraphicsObject;

class WaveShader : public BaseD3DShader {
public:
	WaveShader();
	~WaveShader();

	bool Render(D3DGraphicsObject* graphicsObject, int indexCount, ID3D11ShaderResourceView* texNow, ID3D11ShaderResourceView* texPrev);

	void Compute(_In_ D3DGraphicsObject* graphicsObject, const Vector3 &mousePos, int pressed, _In_ ID3D11ShaderResourceView* texNow, _In_ ID3D11ShaderResourceView* texPrev, _In_ ID3D11UnorderedAccessView* result) const;
private:
	ShaderDescription GetShaderDescription();
	bool SpecificInitialization(ID3D11Device* device);

private:
	struct ScreenSizeBuffer {
		float screenWidth;
		float screenHeight;
		Vector2 padding;
	};

	struct InputBuffer {
		Vector3 mouse;
		int mousePressed;
	};

	CComPtr<ID3D11Buffer>		mScreenSizeBuffer;
	CComPtr<ID3D11Buffer>		mInputBuffer;
	CComPtr<ID3D11SamplerState> mSampleState;
};

#endif