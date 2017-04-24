#pragma once
#include "stdafx.h"

namespace dxfw
{
	class Vec3
	{
	public:
		//------------------------------------------------------------------------------------------//
		// Data
		//------------------------------------------------------------------------------------------//
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float components[3];
		};

	public:
		//------------------------------------------------------------------------------------------//
		// Con-/Destructors
		//------------------------------------------------------------------------------------------//
		Vec3();
		Vec3(float x, float y, float z);
		~Vec3();

		//------------------------------------------------------------------------------------------//
		// Member Functions
		//------------------------------------------------------------------------------------------//
		inline float GetLengthSquare();
		inline float GetLength();
		inline void SetLength(float length);
		inline void Normalize();
		inline Vec3 GetNormalized();

		//------------------------------------------------------------------------------------------//
		// Static Functions
		//------------------------------------------------------------------------------------------//
		static float Dot(const Vec3 &a, const Vec3 &b);
		static Vec3 Cross(const Vec3 &a, const Vec3 &b);
		static float Distance(const Vec3 &a, const Vec3 &b);
		static float AngleBetweenRad(const Vec3 &a, const Vec3 &b);
		static float AngleBetweenDeg(const Vec3 &a, const Vec3 &b);
		static Vec3 Reflect(const Vec3 &v, const Vec3 &n);

		//------------------------------------------------------------------------------------------//
		// Operator Overloads
		//------------------------------------------------------------------------------------------//
		inline Vec3 operator+(const Vec3 &other);
		inline Vec3 operator-(const Vec3 &other);
		//------------------------------------------------------------------------------------------//
		inline Vec3 operator+(const Vec3 &&other);
		inline Vec3 operator-(const Vec3 &&other);
		//------------------------------------------------------------------------------------------//
		inline void operator+=(const Vec3 &other);
		inline void operator-=(const Vec3 &other);
		//------------------------------------------------------------------------------------------//
		inline void operator+=(const Vec3 &&other);
		inline void operator-=(const Vec3 &&other);
		//------------------------------------------------------------------------------------------//
		inline Vec3 operator*(const float &other);
		inline Vec3 operator/(const float &other);
		//------------------------------------------------------------------------------------------//
		inline Vec3 operator*(const float &&other);
		inline Vec3 operator/(const float &&other);
		//------------------------------------------------------------------------------------------//
		inline void operator*=(const float &other);
		inline void operator/=(const float &other);
		//------------------------------------------------------------------------------------------//
		inline void operator*=(const float &&other);
		inline void operator/=(const float &&other);
		//------------------------------------------------------------------------------------------//

	};

	//------------------------------------------------------------------------------------------//
	// Non-Member Operator Overloads
	//------------------------------------------------------------------------------------------//
	inline Vec3 operator*(const float &scalar, const Vec3 &vec);
	inline Vec3 operator/(const float &scalar, const Vec3 &vec);

	inline Vec3 operator+(const Vec3 &a, const Vec3 &b);
	inline Vec3 operator-(const Vec3 &a, const Vec3 &b);
}

#include "Vec3.hpp"