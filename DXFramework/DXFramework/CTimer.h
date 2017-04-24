#pragma once
#include "stdafx.h"

namespace dxfw
{
	class CTimer
	{
	public:
		CTimer();
		~CTimer();

		static double GetSystemTimeInSeconds();
	};
}
