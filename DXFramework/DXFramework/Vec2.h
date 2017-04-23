#pragma once
#include "stdafx.h"

class Vec2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};
		float components[2];
	};
			
public:
	//------------------------------------------------------------------------------------------//
	// Con-/Destructors
	//------------------------------------------------------------------------------------------//
	inline Vec2();
	inline Vec2(float x, float y);
	inline ~Vec2();

	//------------------------------------------------------------------------------------------//
	// Member Functions
	//------------------------------------------------------------------------------------------//
	inline float GetLengthSquare() const;
	inline float GetLength() const;
	inline void SetLength(float length);
	inline void Normalize();
	inline Vec2 GetNormalized() const;
	inline float GetAngleCounterClockwiseRad() const;
	inline float GetAngleCounterClockwiseDeg() const;

	//------------------------------------------------------------------------------------------//
	// Static Functions
	//------------------------------------------------------------------------------------------//
	inline static float Dot(const Vec2 &a, const Vec2 &b);
	inline static float Distance(const Vec2 &a, const Vec2 &b);
	inline static float AngleBetweenRad(const Vec2 &a, const Vec2 &b);
	inline static float AngleBetweenDeg(const Vec2 &a, const Vec2 &b);
	inline static Vec2 Reflect(const Vec2 &v, const Vec2 &n);

	//------------------------------------------------------------------------------------------//
	// Operator Overloads
	//------------------------------------------------------------------------------------------//
	inline Vec2 operator+(const Vec2 &other);
	inline Vec2 operator-(const Vec2 &other);
	//------------------------------------------------------------------------------------------//
	inline Vec2 operator+(const Vec2 &&other);
	inline Vec2 operator-(const Vec2 &&other);
	//------------------------------------------------------------------------------------------//
	inline void operator+=(const Vec2 &other);
	inline void operator-=(const Vec2 &other);
	//------------------------------------------------------------------------------------------//
	inline void operator+=(const Vec2 &&other);
	inline void operator-=(const Vec2 &&other);
	//------------------------------------------------------------------------------------------//
	inline Vec2 operator*(const float &other);
	inline Vec2 operator/(const float &other);
	//------------------------------------------------------------------------------------------//
	inline Vec2 operator*(const float &&other);
	inline Vec2 operator/(const float &&other);
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
inline Vec2 operator*(const float &scalar, const Vec2 &vec);
inline Vec2 operator/(const float &scalar, const Vec2 &vec);

inline Vec2 operator+(const Vec2 &a, const Vec2 &b);
inline Vec2 operator-(const Vec2 &a, const Vec2 &b);

#include "Vec2.hpp"