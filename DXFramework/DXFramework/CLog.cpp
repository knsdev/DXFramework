#include "stdafx.h"
#include "CLog.h"

namespace dxfw
{
	void CLog::Print(const std::string& message)
	{
		std::cout << message << std::endl;
	}

	void CLog::PrintVec2(DirectX::XMVECTOR vector, const char* message)
	{
		DirectX::XMFLOAT2 v2;
		DirectX::XMStoreFloat2(&v2, vector);

		if (message != nullptr)
		{
			std::cout << message << " = ";
		}

		std::cout << "(" << v2.x << "|" << v2.y << ")" << std::endl;
	}

	void CLog::PrintVec3(DirectX::XMVECTOR vector, const char* message)
	{
		DirectX::XMFLOAT3 v3;
		DirectX::XMStoreFloat3(&v3, vector);

		if (message != nullptr)
		{
			std::cout << message << " = ";
		}

		std::cout << "(" << v3.x << "|" << v3.y << "|" << v3.z << ")" << std::endl;
	}

	void CLog::PrintVec4(DirectX::XMVECTOR vector, const char* message)
	{
		DirectX::XMFLOAT4 v4;
		DirectX::XMStoreFloat4(&v4, vector);

		if (message != nullptr)
		{
			std::cout << message << " = ";
		}

		std::cout << "(" << v4.x << "|" << v4.y << "|" << v4.z << "|" << v4.w << ")" << std::endl;
	}
}