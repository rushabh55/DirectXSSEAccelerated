/***************************************************************
MainSystem.cpp

Author: Valentin Hinov
Date: 02/09/2013
Version: 1.0
**************************************************************/
#include <stdlib.h>     
#include <time.h>       
#include <windowsx.h>
#include <iostream>
#include "MainSystem.h"
#include "GraphicsSystemImpl.h"
#include "InputSystemImpl.h"
#include "../utilities/Physics.h"

MainSystem::MainSystem() : mTimeLag(0.0f) {
}


MainSystem::MainSystem(const MainSystem& other) {
}


MainSystem::~MainSystem() {
	// Shutdown the window.
	ShutdownWindows();

}


bool MainSystem::Initialize() {
	int screenWidth, screenHeight;
	bool result;

	// Seed RNG
	srand((UINT)time(NULL));

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	mGraphics = unique_ptr<GraphicsSystemImpl>(new GraphicsSystemImpl());

	// Create the input system object
	mInput = unique_ptr<InputSystemImpl>(new InputSystemImpl());

	// Register all systems with the service provider
	ServiceProvider::Instance().RegisterService(static_cast<InputSystem*>(mInput.get()));
	ServiceProvider::Instance().RegisterService(static_cast<IGraphicsSystem*>(mGraphics.get()));
	ServiceProvider::Instance().RegisterService(static_cast<IAppTimer*>(&mAppTimer));

	if (!mGraphics || !mInput)
		return false;

	// Init input
	result = mInput->Initialize(mHInstance, mHwnd);
	if (!result) {
		return false;
	}

	// Initialize performance monitor
	result = mPerfMonitor.Initialize();
	if (!result) {
		return false;
	}

	// Initialize the graphics object.
	result = mGraphics->Initialize(screenWidth, screenHeight, mHwnd);
	if(!result) {
		return false;
	}
	
	return true;
}

void MainSystem::Run() {
	MSG msg;
	bool done, result;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Initialize AppTimer
	mAppTimer.Reset();

	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done) {
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT) {
			done = true;
		}
		else {			
			result = Frame();

			if(!result) {
				done = true;
			}	
		}
	}

	return;
}

bool MainSystem::Frame() {
	bool result;

	mAppTimer.Tick();
	mPerfMonitor.Tick();

	float deltaTime = mAppTimer.GetDeltaTime();
	mTimeLag += deltaTime;

	mInput->Update(deltaTime);

	// Check if the user pressed escape and wants to exit the application.
	if(mInput->IsKeyDown(VK_ESCAPE)) {
		return false;
	}

	// Let game physics catch up
	float fMaxSimTimestep = Physics::fMaxSimulationTimestep;
	while (mTimeLag >= fMaxSimTimestep) {
		mGraphics->FixedFrame(fMaxSimTimestep);
		mTimeLag -= fMaxSimTimestep;
	}

	// Do the frame processing for the graphics object.
	result = mGraphics->Frame(deltaTime);
	if(!result) {
		return false;
	}

	// set the FPS counter in the graphics
	mGraphics->SetMonitorData(mAppTimer.GetFps(), mPerfMonitor.GetCpuPercentage());

	if (mInput->IsKeyDown(VK_SHIFT) && mInput->IsKeyDown('P')) {
		mGraphics->TakeScreenshot(L"Screenshot.jpg");
		mInput->KeyUp(VK_SHIFT);
		mInput->KeyUp('P');
	}

	mInput->PostUpdate();

	return true;
}

LRESULT CALLBACK MainSystem::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	//if (TwEventWin(hwnd,umsg,wparam,lparam)) { // send event message to AntTweakBar
	//	return 0; // event has been handled by AntTweakBar
	//}
	switch(umsg) {
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			mInput->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			mInput->KeyUp((unsigned int)wparam);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			SetCapture(hwnd);
			mInput->OnMouseButtonAction(0,true);
			return 0;
		}

		case WM_LBUTTONUP:
		{
			ReleaseCapture();
			mInput->OnMouseButtonAction(0,false);
			return 0;
		}

		case WM_RBUTTONDOWN:
		{
			SetCapture(hwnd);
			mInput->OnMouseButtonAction(1,true);
			return 0;
		}

		case WM_RBUTTONUP:
		{
			ReleaseCapture();
			mInput->OnMouseButtonAction(1,false);
			return 0;
		}

		case WM_MBUTTONDOWN:
		{
			SetCapture(hwnd);
			mInput->OnMouseButtonAction(2,true);
			return 0;
		}

		case WM_MBUTTONUP:
		{
			ReleaseCapture();
			mInput->OnMouseButtonAction(2,false);
			return 0;
		}
		
		case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lparam);
			int yPos = GET_Y_LPARAM(lparam);
			mInput->SetMousePos(xPos,yPos);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

void MainSystem::InitializeWindows(int& screenWidth, int& screenHeight) {
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	mHInstance = GetModuleHandle(NULL);

	// Give the application a name.
	mApplicationName = L"Fluid Simulation";

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = mHInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = mApplicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = SCREEN_WIDTH_WINDOWED;
		screenHeight = SCREEN_HEIGHT_WINDOWED;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;		
	}

	// Create the window with the screen settings and get the handle to it.
	mHwnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName, 
							WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, screenWidth, screenHeight, NULL, NULL, mHInstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd);
	SetFocus(mHwnd);

	// Show the mouse cursor.
	ShowCursor(true);
}

void MainSystem::ShutdownWindows() {
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(mHwnd);
	mHwnd = NULL;

	// Remove the application instance.
	UnregisterClass(mApplicationName, mHInstance);
	mHInstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch(umessage)
	{
		case WM_CREATE:
		{
			return 0;
		}
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}