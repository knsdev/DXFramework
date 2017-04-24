#pragma once
#include "stdafx.h"

namespace dxfw
{
	enum class ESysWinMode
	{
		Windowed,
		Borderless,
		Fullscreen
	};

	struct SAppConfig
	{
		wchar_t* pWindowName;
		int width;
		int height;
		ESysWinMode mode;
		bool vsync;
		UINT numFixedUpdatesPerSecond;
	};
}
