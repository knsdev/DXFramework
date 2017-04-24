#pragma once
#include "stdafx.h"
#include "ISysWinEventHandler.h"
#include "SAppConfig.h"

namespace dxfw
{
	class CSysWindow
	{
	public:
		CSysWindow(ISysWinEventHandler* pEventHandler, const SAppConfig& config);
		virtual ~CSysWindow();

		void Init();
		void RunMessageLoop();

		const std::wstring& GetWindowName() const { return m_windowName; }
		int GetClientWidth() const { return m_clientWidth; }
		int GetClientHeight() const { return m_clientHeight; }
		ESysWinMode GetMode() const { return m_mode; }
		const HWND GetHandle() const { return m_hwnd; }

	private:
		CSysWindow(const CSysWindow &) {}
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		static ISysWinEventHandler* m_pEventHandler;
		static const wchar_t* m_pClassName;
		static std::wstring m_windowName;
		static int m_clientWidth;
		static int m_clientHeight;
		static ESysWinMode m_mode;
		static HWND m_hwnd;
		static bool m_quit;
	};
}
