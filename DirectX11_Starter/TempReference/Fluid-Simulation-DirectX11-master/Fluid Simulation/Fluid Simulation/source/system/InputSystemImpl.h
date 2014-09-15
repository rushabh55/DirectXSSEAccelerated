/*************************************************************
InputSystem.h: Specific Implementation of the 
engine input system. 

Author: Valentin Hinov
Date: 02/09/2013
**************************************************************/
#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

struct IDirectInput8;
struct IDirectInputDevice8;
struct _DIMOUSESTATE;
typedef _DIMOUSESTATE DIMOUSESTATE;

#include "InputSystem.h"

class InputSystemImpl : public InputSystem {
public:
	InputSystemImpl();
	InputSystemImpl(const InputSystemImpl&);
	~InputSystemImpl();

	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void Update(float delta);
	void PostUpdate();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	void SetMousePos(int x, int y);

	// change in mouse key status
	// 0 - Left
	// 1 - Right
	// 2 - Mid
	void OnMouseButtonAction(int key, bool status);

	bool IsKeyDown(unsigned int) const;
	bool IsKeyClicked(unsigned int) const;

	bool IsMouseLeftDown() const;
	bool IsMouseRightDown() const;
	bool IsMouseMidDown() const;

	bool IsMouseLeftClicked() const;
	bool IsMouseRightClicked() const;
	bool IsMouseMidClicked() const;

	void GetMousePos(int& xPos, int& yPos) const;
	void GetMouseDelta(int& xDelta, int& yDelta) const;
	void GetMouseScrollDelta(int &scrollDelta) const;

private:
	bool mKeys[256];
	int mLastKeyDown;
	bool mMouseLeft,mMouseRight, mMouseMid;
	bool mMouseLeftClicked,mMouseRightClicked,mMouseMidClicked;

	int mMouseX,mMouseY;
	

	// Need direct input for mouse delta
	IDirectInput8* mDirectInput;
	IDirectInputDevice8* mKeyboard;
	IDirectInputDevice8* mMouse;

	DIMOUSESTATE* mMouseState;
};

#endif
