/***************************************************************
D3DGraphicsObject.h: A class that encapsulates a 
D3D graphics object implementation

Author: Valentin Hinov
Date: 02/09/2013
Version: 1.0
**************************************************************/

#ifndef _D3DGRAPHICSOBJECT_H
#define _D3DGRAPHICSOBJECT_H

#define WIN32_LEAN_AND_MEAN
#include "IGraphicsObject.h"

#include "../utilities/AtlInclude.h"

#include "../utilities/D3dIncludes.h"


using namespace std;

class D3DGraphicsObject : public IGraphicsObject {
public:
	D3DGraphicsObject();
	~D3DGraphicsObject();

	bool Initialize(int screenWidth, int screenHeight, bool vSync, HWND hwnd, bool fullScreen, float screenDepth, float screenNear);
	
	void BeginRender(float clearRed, float clearGreen, float clearBlue, float clearAlpha);
	void EndRender();

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;
	ID3D11DepthStencilView* GetDepthStencilView() const;

	void GetVideoCardInfo(char *cardName, int& memory) const;

	void GetWorldMatrix(Matrix&) const;
	void GetOrthoMatrix(Matrix&) const;

	void GetScreenDimensions(int &width, int &height) const;
	void GetScreenDepthInfo(float &nearVal, float &farVal) const;
	
	void SetBackBufferRenderTarget() const;
	void SetZBufferState(bool state) const;
	void SetAlphaBlendState(bool state) const;
	
	void TurnWireframeOn() const;
	void TurnWireframeOff() const;	
	
	bool Screenshot(LPCWSTR name) const;

private:
	bool BuildBlendStates();
	bool BuildDepthStencilStates();

private:
	int		mScreenWidth;
	int		mScreenHeight;
	float	mScreenNear;
	float	mScreenDepth;

	Matrix  mWorldMatrix;
	Matrix  mOrthoMatrix;

	bool	mVsyncEnabled;
	int		mVideoCardMemoryMB;
	char	mVideoCardDescription[128];

	CComPtr<ID3D11BlendState>			mTransparentBS;
	CComPtr<ID3D11BlendState>			mAlphaEnabledBS;
	CComPtr<ID3D11BlendState>			mAlphaDisabledBS;
	
	CComPtr<ID3D11DepthStencilState>  mDepthStencilState;
	CComPtr<ID3D11DepthStencilState>  mDepthDisabledStencilState;
	
	CComPtr<IDXGISwapChain>			mSwapChain;
	CComPtr<ID3D11Device> 			mDevice;
	CComPtr<ID3D11DeviceContext> 	mDeviceContext;
	CComPtr<ID3D11RenderTargetView> mRenderTargetView;
	CComPtr<ID3D11Texture2D> 		mDepthStencilBuffer;
	CComPtr<ID3D11DepthStencilView>	mDepthStencilView;
	CComPtr<ID3D11RasterizerState>	mRasterState;
	CComPtr<ID3D11RasterizerState>	mRasterStateWireframe;
};
#endif