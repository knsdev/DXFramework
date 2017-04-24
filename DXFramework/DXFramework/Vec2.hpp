#pragma once
#include "stdafx.h"
#include "Vec2.h"
#include "CMathHelper.h"

namespace dxfw
{
	//------------------------------------------------------------------------------------------//
	// Con-/Destructors
	//------------------------------------------------------------------------------------------//

	Vec2::Vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vec2::Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2::~Vec2()
	{

	}

	//------------------------------------------------------------------------------------------//
	// Member Functions
	//------------------------------------------------------------------------------------------//

	inline float Vec2::GetLengthSquare() const
	{
		return (x*x + y*y);
	}

	inline float Vec2::GetLength() const
	{
		return std::sqrt(GetLengthSquare());
	}

	inline void Vec2::SetLength(float length)
	{
		this->Normalize();
		(*this) *= length;
	}

	inline void Vec2::Normalize()
	{
		(*this) /= this->GetLength();
	}

	inline Vec2 Vec2::GetNormalized() const
	{
		Vec2 newVec2 = (*this);
		newVec2.Normalize();
		return newVec2;
	}

	inline float Vec2::GetAngleCounterClockwiseRad() const
	{
		Vec2& normalized = this->GetNormalized();
		float angle = std::atan2f(normalized.y, normalized.x);
		return angle;
	}

	inline float Vec2::GetAngleCounterClockwiseDeg() const
	{
		return this->GetAngleCounterClockwiseRad() * CMathHelper::RAD_TO_DEG;
	}

	//------------------------------------------------------------------------------------------//
	// Static Functions
	//------------------------------------------------------------------------------------------//

	inline float Vec2::Dot(const Vec2 &a, const Vec2 &b)
	{
		return a.x * b.x + a.y * b.y;
	}

	inline float Vec2::Distance(const Vec2 &a, const Vec2 &b)
	{
		return (a - b).GetLength();
	}

	inline float Vec2::AngleBetweenRad(const Vec2 &a, const Vec2 &b)
	{
		return std::acos(Dot(a, b));
	}

	inline float Vec2::AngleBetweenDeg(const Vec2 &a, const Vec2 &b)
	{
		return AngleBetweenRad(a, b) * CMathHelper::RAD_TO_DEG;
	}

	inline Vec2 Vec2::Reflect(const Vec2 &v, const Vec2 &normal)
	{
		return (2.0f * Vec2::Dot(-1.0f * v, normal) * normal) + v;
	}

	//------------------------------------------------------------------------------------------//
	// Operator Overloads
	//------------------------------------------------------------------------------------------//

	inline Vec2 Vec2::operator+(const Vec2 &other)
	{
		Vec2 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		return temp;
	}

	inline Vec2 Vec2::operator-(const Vec2 &other)
	{
		Vec2 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		return temp;
	}

	//------------------------------------------------------------------------------------------//

	inline Vec2 Vec2::operator+(const Vec2 &&other)
	{
		Vec2 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		return temp;
	}


	inline Vec2 Vec2::operator-(const Vec2 &&other)
	{
		Vec2 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		return temp;
	}

	//------------------------------------------------------------------------------------------//

	inline void Vec2::operator+=(const Vec2 &other)
	{
		*this = *this + other;
	}


	inline void Vec2::operator-=(const Vec2 &other)
	{
		*this = *this - other;
	}

	//------------------------------------------------------------------------------------------//

	inline void Vec2::operator+=(const Vec2 &&other)
	{
		*this = *this + other;
	}


	inline void Vec2::operator-=(const Vec2 &&other)
	{
		*this = *this - other;
	}

	//------------------------------------------------------------------------------------------//

	inline Vec2 Vec2::operator*(const float &other)
	{
		Vec2 temp;
		temp.x = this->x * other;
		temp.y = this->y * other;
		return temp;
	}

	inline Vec2 Vec2::operator/(const float &other)
	{
		Vec2 temp;
		temp.x = this->x / other;
		temp.y = this->y / other;
		return temp;
	}

	//------------------------------------------------------------------------------------------//

	inline Vec2 Vec2::operator*(const float &&other)
	{
		Vec2 temp;
		temp.x = this->x * other;
		temp.y = this->y * other;
		return temp;
	}

	inline Vec2 Vec2::operator/(const float &&other)
	{
		Vec2 temp;
		temp.x = this->x / other;
		temp.y = this->y / other;
		return temp;
	}

	//------------------------------------------------------------------------------------------//

	inline void Vec2::operator*=(const float &other)
	{
		this->x = this->x * other;
		this->y = this->y * other;
	}

	inline void Vec2::operator/=(const float &other)
	{
		this->x = this->x / other;
		this->y = this->y / other;
	}

	//------------------------------------------------------------------------------------------//

	inline void Vec2::operator*=(const float &&other)
	{
		this->x = this->x * other;
		this->y = this->y * other;
	}


	inline void Vec2::operator/=(const float &&other)
	{
		this->x = this->x / other;
		this->y = this->y / other;
	}

	//------------------------------------------------------------------------------------------//
	// Non-Member Operator Overloads
	//------------------------------------------------------------------------------------------//

	inline Vec2 operator*(const float &scalar, const Vec2 &vec)
	{
		return Vec2(vec.x * scalar, vec.y * scalar);
	}

	inline Vec2 operator/(const float &scalar, const Vec2 &vec)
	{
		return Vec2(vec.x / scalar, vec.y / scalar);
	}

	//------------------------------------------------------------------------------------------//

	inline Vec2 operator+(const Vec2 &a, const Vec2 &b)
	{
		return Vec2(a.x + b.x, a.y + b.y);
	}

	inline Vec2 operator-(const Vec2 &a, const Vec2 &b)
	{
		return Vec2(a.x - b.x, a.y - b.y);
	}
}
