#include "stdafx.h"
#include "CInputManager.h"

namespace dxfw
{
	CInputManager::CInputManager()
	{
		memset(m_keyStates, 0, get_num_keys_total());
	}

	CInputManager::~CInputManager()
	{
	}

	void CInputManager::OnMsgKeyDown(WPARAM wParam, LPARAM lParam)
	{
		UINT keyIndex = 0;

		// 0 = first key down
		// 1 = repeat down
		bool prevKeyState = ((lParam >> 30) & 0x00000001);
		if (prevKeyState == true)
		{
			return;
		}

		if (GetKeyIndex(wParam, keyIndex))
		{
			m_keyStates[keyIndex] = true;
			printf("key down %u\n", keyIndex);
		}
	}

	void CInputManager::OnMsgKeyUp(WPARAM wParam, LPARAM lParam)
	{
		UINT keyIndex = 0;

		if (GetKeyIndex(wParam, keyIndex))
		{
			m_keyStates[keyIndex] = false;
			printf("key up %u\n", keyIndex);
		}
	}

	bool CInputManager::GetKeyIndex(WPARAM wParam, UINT& keyIndex)
	{
		// A-Z
		if (wParam >= 0x41 && wParam <= 0x5A)
		{
			keyIndex = (UINT)wParam - 0x41;
			return true;
		}
		// Alpha 0-9
		if (wParam >= 0x30 && wParam <= 0x39)
		{
			keyIndex = (UINT)wParam - 0x30 + (UINT)EKeyCode::Alpha0;
			return true;
		}
		// F1-F24
		if (wParam >= VK_F1 && wParam <= VK_F24)
		{
			keyIndex = (UINT)wParam - VK_F1 + (UINT)EKeyCode::F1;
			return true;
		}
		// Arrows
		if (wParam >= VK_LEFT && wParam <= VK_DOWN)
		{
			keyIndex = (UINT)wParam - VK_LEFT + (UINT)EKeyCode::ArrowLeft;
			return true;
		}
		// Enter/Return
		if (wParam == VK_RETURN)
		{
			keyIndex = (UINT)EKeyCode::Return;
			return true;
		}
		// Space
		if (wParam == VK_SPACE)
		{
			keyIndex = (UINT)EKeyCode::Space;
			return true;
		}
		// Backspace
		if (wParam == VK_BACK)
		{
			keyIndex = (UINT)EKeyCode::Backspace;
			return true;
		}
		// Escape
		if (wParam == VK_ESCAPE)
		{
			keyIndex = (UINT)EKeyCode::Escape;
			return true;
		}
		// Ctrl
		if (wParam == VK_CONTROL)
		{
			keyIndex = (UINT)EKeyCode::Ctrl;
			return true;
		}
		// Shift
		if (wParam == VK_SHIFT)
		{
			keyIndex = (UINT)EKeyCode::Shift;
			return true;
		}
		// Capslock
		if (wParam == VK_CAPITAL)
		{
			keyIndex = (UINT)EKeyCode::Capslock;
			return true;
		}
		// Tab
		if (wParam == VK_TAB)
		{
			keyIndex = (UINT)EKeyCode::Tab;
			return true;
		}
		// Alt
		if (wParam == VK_MENU)
		{
			keyIndex = (UINT)EKeyCode::Alt;
			return true;
		}
		// Comma
		if (wParam == VK_OEM_COMMA)
		{
			keyIndex = (UINT)EKeyCode::Comma;
			return true;
		}
		// Point
		if (wParam == VK_OEM_PERIOD)
		{
			keyIndex = (UINT)EKeyCode::Point;
			return true;
		}
		// Minus
		if (wParam == VK_OEM_MINUS)
		{
			keyIndex = (UINT)EKeyCode::Minus;
			return true;
		}
		// Plus
		if (wParam == VK_OEM_PLUS)
		{
			keyIndex = (UINT)EKeyCode::Plus;
			return true;
		}
		// Misc1 ü
		if (wParam == VK_OEM_1)
		{
			keyIndex = (UINT)EKeyCode::Misc1;
			return true;
		}
		// Misc2 #
		if (wParam == VK_OEM_2)
		{
			keyIndex = (UINT)EKeyCode::Misc2;
			return true;
		}
		// Misc2 ö
		if (wParam == VK_OEM_3)
		{
			keyIndex = (UINT)EKeyCode::Misc3;
			return true;
		}
		// Misc4 ß
		if (wParam == VK_OEM_4)
		{
			keyIndex = (UINT)EKeyCode::Misc4;
			return true;
		}
		// Misc5 ^
		if (wParam == VK_OEM_5)
		{
			keyIndex = (UINT)EKeyCode::Misc5;
			return true;
		}
		// Misc6 ´
		if (wParam == VK_OEM_6)
		{
			keyIndex = (UINT)EKeyCode::Misc6;
			return true;
		}
		// Misc7 ä
		if (wParam == VK_OEM_7)
		{
			keyIndex = (UINT)EKeyCode::Misc7;
			return true;
		}
		// Misc10 <
		if (wParam == VK_OEM_102)
		{
			keyIndex = (UINT)EKeyCode::Misc10;
			return true;
		}
		// TODO: Setup missing keys

		return false;
	}
}
