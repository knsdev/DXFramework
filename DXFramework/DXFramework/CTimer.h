#pragma once
#include "stdafx.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

	static double GetSystemTimeInSeconds();
};