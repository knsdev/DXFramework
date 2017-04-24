#pragma once
#include "stdafx.h"

namespace dxfw
{
	class CMathHelper
	{
	public:
		template<typename T>
		static T Clamp(T value, T min, T max)
		{
			if (value < min)
			{
				return min;
			}
			else if (value > max)
			{
				return max;
			}
			else
			{
				return value;
			}
		}

		static UINT RGBAtoABGR(UINT rgba)
		{
			BYTE R = (rgba >> 24) & 0xFF;
			BYTE G = (rgba >> 16) & 0xFF;
			BYTE B = (rgba >> 8) & 0xFF;
			BYTE A = (rgba) & 0xFF;
			UINT ABGR = (A << 24) | (B << 16) | (G << 8) | (R);
			return ABGR;
		}

		static UUID GetNewGUID()
		{
			UUID uuid;
			if (UuidCreate(&uuid) == RPC_S_UUID_NO_ADDRESS)
			{
				throw std::exception("GetNewGUID");
			}
			return uuid;
		}

		static float PI;
		static float RAD_TO_DEG;
		static float DEG_TO_RAD;
	};
}