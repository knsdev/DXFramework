#pragma once
#include "stdafx.h"

namespace dxfw
{
	class CLog
	{
	public:
		static void Print(const std::string& message);
		static void PrintVec2(DirectX::XMVECTOR vector, const char* message = nullptr);
		static void PrintVec3(DirectX::XMVECTOR vector, const char* message = nullptr);
		static void PrintVec4(DirectX::XMVECTOR vector, const char* message = nullptr);
	};
}