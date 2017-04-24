#include "stdafx.h"
#include "CTimer.h"

namespace dxfw
{
	CTimer::CTimer()
	{
	}

	CTimer::~CTimer()
	{
	}

	double CTimer::GetSystemTimeInSeconds()
	{
		int64_t frequency;
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

		int64_t ticks;
		QueryPerformanceCounter((LARGE_INTEGER*)&ticks);

		double result = ticks / (double)frequency;

		return result;
	}
}
