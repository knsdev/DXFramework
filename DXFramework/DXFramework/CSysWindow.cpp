#include "stdafx.h"
#include "CSysWindow.h"

namespace dxfw
{
	ISysWinEventHandler* CSysWindow::m_pEventHandler = nullptr;
	const wchar_t* CSysWindow::m_pClassName;
	std::wstring CSysWindow::m_windowName;
	int CSysWindow::m_clientWidth;
	int CSysWindow::m_clientHeight;
	ESysWinMode CSysWindow::m_mode;
	HWND CSysWindow::m_hwnd;
	bool CSysWindow::m_quit = false;

	LRESULT CALLBACK CSysWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			m_pEventHandler->OnQuit();
			PostQuitMessage(0);
			m_quit = true;
			return 0;
		case WM_SIZE:
			m_clientWidth = LOWORD(lParam);
			m_clientHeight = HIWORD(lParam);
			m_pEventHandler->OnResize(wParam == SIZE_MINIMIZED, m_clientWidth, m_clientHeight);
			return 0;
		case WM_LBUTTONDOWN:
		{
			int mx = GET_X_LPARAM(lParam);
			int my = GET_Y_LPARAM(lParam);
			//printf_s("WM_LBUTTONDOWN: MousePos = (%d | %d)\n", mx, my);
			return 0;
		}
		case WM_KEYDOWN:
		{
			//printf("VK: %x\n", wParam);
			m_pEventHandler->OnMsgKeyDown(wParam, lParam);
			return 0;
		}
		case WM_KEYUP:
		{
			m_pEventHandler->OnMsgKeyUp(wParam, lParam);
			return 0;
		}
		case WM_SYSKEYDOWN:
		{
			m_pEventHandler->OnMsgKeyDown(wParam, lParam);
		}
		case WM_SYSKEYUP:
		{
			m_pEventHandler->OnMsgKeyUp(wParam, lParam);
		}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	CSysWindow::CSysWindow(ISysWinEventHandler* pEvtHandler, const SAppConfig& config)
	{
		m_pEventHandler = pEvtHandler;
		m_windowName = config.pWindowName;
		m_clientWidth = config.width;
		m_clientHeight = config.height;
		m_mode = config.mode;
		m_pClassName = L"DXWNDCLASSEX";
	}

	CSysWindow::~CSysWindow()
	{
		UnregisterClass(m_pClassName, NULL);
	}

	void CSysWindow::Init()
	{
		WNDCLASSEX wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = m_pClassName;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClassEx(&wc);

		DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		DWORD dwStyleEx = WS_EX_OVERLAPPEDWINDOW;

		switch (m_mode)
		{
		case ESysWinMode::Windowed:
			break;
		case ESysWinMode::Borderless:
			dwStyleEx = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
			break;
		case ESysWinMode::Fullscreen:
			break;
		}

		RECT rectWnd = { 0, 0, m_clientWidth, m_clientHeight };
		AdjustWindowRectEx(&rectWnd, dwStyle, FALSE, dwStyleEx);

		m_hwnd = CreateWindowEx(dwStyleEx, // dwExStyle
			m_pClassName, // lpClassName
			m_windowName.c_str(), // lpWindowName
			dwStyle, // dwStyle
			GetSystemMetrics(SM_CXSCREEN) / 2 - m_clientWidth / 2, // x pos
			GetSystemMetrics(SM_CYSCREEN) / 2 - m_clientHeight / 2, // y pos
			rectWnd.right - rectWnd.left, // width
			rectWnd.bottom - rectWnd.top, // height
			NULL, // hWndParent [in, optional]
			NULL, // hMenu [in, optional]
			GetModuleHandle(NULL), // hInstance [in, optional]
			NULL); // lpParam [in, optional]

		if (m_hwnd == NULL)
		{
			printf_s("CreateWindowEx failed!");
			return;
		}

		ShowWindow(m_hwnd, 1);
	}

	void CSysWindow::RunMessageLoop()
	{
		while (!m_quit)
		{
			MSG msg;
			if (PeekMessage(&msg, m_hwnd, NULL, NULL, PM_REMOVE) != 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				m_pEventHandler->OnUpdate();
			}
		}
	}
}
