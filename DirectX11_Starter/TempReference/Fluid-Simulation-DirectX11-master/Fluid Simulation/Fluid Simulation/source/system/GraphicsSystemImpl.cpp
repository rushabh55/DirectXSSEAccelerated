/***************************************************************
GraphicsSystem.h: In charge of displaying content on the screen.
Calls Render on the current active Scene and renders the GUI
overlay. 

Author: Valentin Hinov
Date: 02/09/2013
**************************************************************/
#include <AntTweakBar.h>
#include "GraphicsSystemImpl.h"
#include "ServiceProvider.h"

#if defined (D3D)
#include "SpriteFont.h"
#include "CommonStates.h"
#include "../display/D3DGraphicsObject.h"
using namespace DirectX;
#endif

#include "../display/Scenes/Fluid2DScene.h"
#include "../display/Scenes/Fluid3DScene.h"
#include "../display/Scenes/RigidBodyScene3D.h"
#include "../utilities/Screen.h"
#include "../utilities/Physics.h"
#include "../utilities/StringUtils.h"

/// ANT TWEAK BAR CALLBACKS ///
void TW_CALL ResetCallback(void *clientData) {
	GraphicsSystemImpl *thisSystem = static_cast<GraphicsSystemImpl*>(clientData);
	bool result = thisSystem->ResetScene();
	if (!result) {
		// reset failed
	}
}

void TW_CALL SingleStepPhysics(void *clientData) {
	GraphicsSystemImpl *thisSystem = static_cast<GraphicsSystemImpl*>(clientData);
	thisSystem->GetCurrentScene()->FixedUpdate(Physics::fMaxSimulationTimestep);
}
/// ~ANT TWEAK BAR CALLBACKS ///


GraphicsSystemImpl::GraphicsSystemImpl() : 
	mSceneFixedUpdatePaused(false), mReverseFixedTimestep(false), mRenderOverlay(true),
	mFps(0), mAverageFps(0), mMaximumFps(0), mMinimumFps(100000), mNumFrames(0), mTotalFps(0)
{
	mFps = mCpuUsage = 0;
}

GraphicsSystemImpl::GraphicsSystemImpl(const GraphicsSystemImpl& other) {
}

GraphicsSystemImpl::~GraphicsSystemImpl() {
	// Terminate AntTweakBar
	int result = TwTerminate();
	if (result == 0) {
		// AntTweakBar did not terminate properly
	}
}

bool GraphicsSystemImpl::Initialize(int screenWidth, int screenHeight, HWND hwnd) {
	mHwnd = hwnd;

	#if defined (D3D)
		mGraphicsObj = unique_ptr<IGraphicsObject>(new D3DGraphicsObject());
	#endif

	if (!mGraphicsObj) {
		return false;
	}

	D3DGraphicsObject *d3dObject = dynamic_cast<D3DGraphicsObject*>(mGraphicsObj.get());

	bool result = mGraphicsObj->Initialize(screenWidth,screenHeight,VSYNC_ENABLED,hwnd,FULL_SCREEN,SCREEN_DEPTH,SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Graphics Object", L"Error", MB_OK);
		return false;
	}

	mGraphicsObj->GetScreenDimensions(Screen::width, Screen::height);

	// Initialize AntTweak before the current scene
	TwInit(TW_DIRECT3D11, d3dObject->GetDevice());
	TwWindowSize(screenWidth,screenHeight);

	// Initialize font
	mSpriteBatch = shared_ptr<SpriteBatch>(new SpriteBatch(d3dObject->GetDeviceContext()));
	mSpriteFont = shared_ptr<SpriteFont>(new SpriteFont(d3dObject->GetDevice(), L"data/TBNA.spritefont"));
	mCommonStates = shared_ptr<CommonStates>(new CommonStates(d3dObject->GetDevice()));

	// Initialize current scene
	ResetScene();

	// Initialize the main tweak bar
	TwBar *twBar;
	twBar = TwNewBar("MainControl");
	// Position bar
	int barPos[2] = {1,screenHeight-100};
	TwSetParam(twBar,nullptr,"position", TW_PARAM_INT32, 2, barPos);
	int barSize[2] = {200,100};
	TwSetParam(twBar,nullptr,"size", TW_PARAM_INT32, 2, barSize);
	TwDefine(" MainControl iconified=true ");
	TwAddButton(twBar,"Reset Scene", ResetCallback, this, " key=r ");// The R key resets the scene
	TwAddVarRW(twBar, "Render Overlay", TW_TYPE_BOOLCPP, &mRenderOverlay, " key=o ");
	TwAddVarRW(twBar, "Pause Physics", TW_TYPE_BOOLCPP, &mSceneFixedUpdatePaused, " key=p ");
	TwAddVarRW(twBar, "Sim Max Timestep", TW_TYPE_FLOAT, &Physics::fMaxSimulationTimestep, " min=0.005 max=1.0 step=0.001 ");


	// Get video card info
	int cardMemory = 0;
	char cardName[128];
	mGraphicsObj->GetVideoCardInfo(cardName, cardMemory);
	string cardNameString = cardName;
	mCardName = StrToWidestr(cardNameString);
	mVideoMemory = to_wstring(cardMemory);

	return true;
}

bool GraphicsSystemImpl::ResetScene() {
	mCurrentScene.reset(new Fluid3DScene());
	bool result = mCurrentScene->Initialize(mGraphicsObj.get(),mHwnd);
	if (!result) {
		MessageBox(mHwnd, L"Could not initialize the scene", L"Error", MB_OK);
		return false;
	}
	return true;
}

bool GraphicsSystemImpl::Frame(float delta) {
	mCurrentScene->Update(delta);
	return Render();
}

void GraphicsSystemImpl::FixedFrame(float fixedDelta) const {
	if (!mSceneFixedUpdatePaused) {
		mCurrentScene->FixedUpdate(fixedDelta);
	}
}

bool GraphicsSystemImpl::Render() const {
	// first obtain all the needed matrices
	bool result;

	// Start rendering
	mGraphicsObj->BeginRender(0.32f,0.31f,0.31f,1.0f);
	{
		result = mCurrentScene->Render();
		if (!result) {
			return false;
		}
		result = RenderOverlay();
		if (!result) {
			return false;
		}
	}
	// Finish rendering and display
	mGraphicsObj->EndRender();

	return true;
}

bool GraphicsSystemImpl::RenderOverlay() const {
	// Render overlay information
	if (mRenderOverlay)	{
		mSpriteBatch->Begin();
		{
			// Display Current FPS
			wstring text = L"Current FPS: " + std::to_wstring(mFps);
			mSpriteFont->DrawString(mSpriteBatch.get(),text.c_str(),XMFLOAT2(10,10));

			text = L"Max FPS: " + std::to_wstring(mMaximumFps);
			mSpriteFont->DrawString(mSpriteBatch.get(),text.c_str(),XMFLOAT2(10,35));

			text = L"Min FPS: " + std::to_wstring(mMinimumFps);
			mSpriteFont->DrawString(mSpriteBatch.get(),text.c_str(),XMFLOAT2(10,60));

			text = L"Average FPS: " + std::to_wstring(mAverageFps);
			mSpriteFont->DrawString(mSpriteBatch.get(),text.c_str(),XMFLOAT2(10,85));

			// Display Card Name
			mSpriteFont->DrawString(mSpriteBatch.get(),mCardName.c_str(),XMFLOAT2(10,110));

			// Display Card Memory
			text = L"Video Memory: " + mVideoMemory + L"MB";
			mSpriteFont->DrawString(mSpriteBatch.get(),text.c_str(),XMFLOAT2(10,135));

			// Allow the current scene to render any additional overlay items
			mCurrentScene->RenderOverlay(mSpriteBatch, mSpriteFont);
		}
		mSpriteBatch->End();
	}
	
	// Render Ant Tweak Bar
	int twResult = TwDraw();
	if (twResult == 0) {
		// TWDraw failed, use TwGetLastError to retrieve error
		return false;
	}

	return true;
}

bool GraphicsSystemImpl::TakeScreenshot(LPCWSTR name) const {
	return mGraphicsObj->Screenshot(name);
}

const IGraphicsObject * const GraphicsSystemImpl::GetGraphicsObject() const {
	return mGraphicsObj.get();
}

IScene * const GraphicsSystemImpl::GetCurrentScene() const {
	return mCurrentScene.get();
}

shared_ptr<DirectX::CommonStates> GraphicsSystemImpl::GetCommonD3DStates() const {
	return mCommonStates;
}

shared_ptr<DirectX::SpriteFont> GraphicsSystemImpl::GetSpriteFont() const {
	return mSpriteFont;
}

void GraphicsSystemImpl::SetMonitorData(int fps, int cpuUsage) {
	mFps = fps;
	mCpuUsage = cpuUsage;
	++mNumFrames;

	// start tracking after 200 frames
	if (mNumFrames > 200) {
		mMaximumFps = max(mFps, mMaximumFps);
		mMinimumFps = min(mFps, mMinimumFps);
		mTotalFps += mFps;
		mAverageFps = mTotalFps/(mNumFrames - 200);
		
	}
}