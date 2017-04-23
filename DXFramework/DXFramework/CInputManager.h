#pragma once
#include "stdafx.h"
#include "EKeyCode.h"

class CInputManager
{
public:
	CInputManager();
	~CInputManager();

	void OnMsgKeyDown(WPARAM wParam, LPARAM lParam);
	void OnMsgKeyUp(WPARAM wParam, LPARAM lParam);

	bool GetKeyState(EKeyCode keyCode) { return m_keyStates[(UINT)keyCode]; }

private:
	bool GetKeyIndex(WPARAM wParam, UINT& keyIndex);

private:
	bool m_keyStates[get_num_keys_total()];
	// TODO: store prevKeyStates (of previous frame) and compare previous with current state in functions like IsKeyDown, IsKeyUp
};