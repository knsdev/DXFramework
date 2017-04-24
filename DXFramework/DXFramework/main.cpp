#include "stdafx.h"
#include "ISysWinEventHandler.h"
#include "CBaseApp.h"
#include "CSysWindow.h"
#include "CTestApp.h"

#ifdef _DEBUG
int main()
{
	using namespace dxfw;

	try
	{
		SAppConfig config = { L"DirectX", 1024, 768, ESysWinMode::Windowed, false, 60 };
		//SAppConfig config = { L"DirectX", 1920, 1200, ESysWinMode::Borderless, false, 60 };
		CTestApp app(config);
		app.Run();
	}
	catch (std::exception& ex)
	{
		std::cout << "Exception: " << ex.what() << std::endl;
		system("pause");
	}

	return 0;
}
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace dxfw;

	try
	{
		//SAppConfig config = { L"DirectX", 1024, 768, ESysWinMode::Windowed, false, 60 };
		SAppConfig config = { L"DirectX", 1920, 1200, ESysWinMode::Borderless, false, 60 };
		CTestApp app(config);
		app.Run();
	}
	catch (std::exception& ex)
	{
		// TODO: Handle Exception in Release Build
	}

	return 0;
}
#endif