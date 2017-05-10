#pragma once
#include "stdafx.h"
#include "EKeyCode.h"

namespace dxfw
{
	class CInputManager
	{
	public:
		CInputManager();
		~CInputManager();

		void OnMsgKeyDown(WPARAM wParam, LPARAM lParam);
		void OnMsgKeyUp(WPARAM wParam, LPARAM lParam);
		void OnMsgMouseMove(WPARAM wParam, LPARAM lParam);
		void OnMsgMouseButtonDown(WPARAM wParam, LPARAM lParam, EKeyCode keyCode);
		void OnMsgMouseButtonUp(WPARAM wParam, LPARAM lParam, EKeyCode keyCode);

		bool GetKeyState(EKeyCode keyCode) { return m_keyStates[(UINT)keyCode] == true; }
		bool IsKeyDown(EKeyCode keyCode) { return m_keyStates[(UINT)keyCode] == true && m_keyStatesPrev[(UINT)keyCode] == false; }
		bool IsKeyUp(EKeyCode keyCode) { return m_keyStates[(UINT)keyCode] == false && m_keyStatesPrev[(UINT)keyCode] == true; }
		POINT GetMousePosition();

	private:
		bool GetKeyIndex(WPARAM wParam, UINT& keyIndex);
		void UpdateKeyState(UINT keyIndex, bool state);

	private:
		bool m_keyStates[get_num_keys_total()];
		bool m_keyStatesPrev[get_num_keys_total()];
	};
}
