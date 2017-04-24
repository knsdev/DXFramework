#pragma once
#include "stdafx.h"

namespace dxfw
{
	class ISysWinEventHandler
	{
	public:
		virtual void OnUpdate() = 0;
		virtual void OnResize(bool minimized, int clientWidth, int clientHeight) = 0;
		virtual void OnQuit() = 0;
		virtual void OnMsgKeyDown(WPARAM wParam, LPARAM lParam) = 0;
		virtual void OnMsgKeyUp(WPARAM wParam, LPARAM lParam) = 0;
	};
}
