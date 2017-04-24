#pragma once
#include "stdafx.h"
#include "Vec3.h"
#include "CMathHelper.h"

namespace dxfw
{
	//------------------------------------------------------------------------------------------//
	// Constructors
	//------------------------------------------------------------------------------------------//

	Vec3::Vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vec3::Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3::~Vec3()
	{

	}
	//------------------------------------------------------------------------------------------//
	// Member Functions
	//------------------------------------------------------------------------------------------//

	inline float Vec3::GetLengthSquare()
	{
		return (x*x + y*y + z*z);
	}

	inline float Vec3::GetLength()
	{
		return std::sqrt(GetLengthSquare());
	}

	inline void Vec3::SetLength(float length)
	{
		this->Normalize();
		(*this) *= length;
	}

	inline void Vec3::Normalize()
	{
		(*this) /= this->GetLength();
	}

	inline Vec3 Vec3::GetNormalized()
	{
		Vec3 newVec3 = (*this);
		newVec3.Normalize();
		return newVec3;
	}

	//------------------------------------------------------------------------------------------//
	// Static Functions
	//------------------------------------------------------------------------------------------//

	inline float Vec3::Dot(const Vec3 &a, const Vec3 &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline Vec3 Vec3::Cross(const Vec3 &a, const Vec3 &b)
	{
		Vec3 newVec3;
		newVec3.x = a.y * b.z - a.z * b.y;
		newVec3.y = a.z * b.x - a.x * b.z;
		newVec3.z = a.x * b.y - a.y * b.x;
		return newVec3;
	}

	inline float Vec3::Distance(const Vec3 &a, const Vec3 &b)
	{
		return (a - b).GetLength();
	}

	inline float Vec3::AngleBetweenRad(const Vec3 &a, const Vec3 &b)
	{
		return std::acos(Dot(a, b));
	}

	inline float Vec3::AngleBetweenDeg(const Vec3 &a, const Vec3 &b)
	{
		return AngleBetweenRad(a, b) * CMathHelper::RAD_TO_DEG;
	}

	inline Vec3 Vec3::Reflect(const Vec3 &v, const Vec3 &normal)
	{
		return (2.0f * Vec3::Dot(-1.0f * v, normal) * normal) + v;
	}

	//------------------------------------------------------------------------------------------//
	// Operator Overloads
	//------------------------------------------------------------------------------------------//

	inline Vec3 Vec3::operator+(const Vec3 &other)
	{
		Vec3 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		temp.z = this->z + other.z;
		return temp;
	}


	inline Vec3 Vec3::operator-(const Vec3 &other)
	{
		Vec3 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		temp.z = this->z - other.z;
		return temp;
	}
	//------------------------------------------------------------------------------------------//

	inline Vec3 Vec3::operator+(const Vec3 &&other)
	{
		Vec3 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		temp.z = this->z + other.z;
		return temp;
	}


	inline Vec3 Vec3::operator-(const Vec3 &&other)
	{
		Vec3 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		temp.z = this->z - other.z;
		return temp;
	}
	//------------------------------------------------------------------------------------------//

	inline void Vec3::operator+=(const Vec3 &other)
	{
		*this = *this + other;
	}


	inline void Vec3::operator-=(const Vec3 &other)
	{
		*this = *this - other;
	}
	//------------------------------------------------------------------------------------------//

	inline void Vec3::operator+=(const Vec3 &&other)
	{
		*this = *this + other;
	}


	inline void Vec3::operator-=(const Vec3 &&other)
	{
		*this = *this - other;
	}
	//------------------------------------------------------------------------------------------//

	inline Vec3 Vec3::operator*(const float &other)
	{
		Vec3 temp;
		temp.x = this->x * other;
		temp.y = this->y * other;
		temp.z = this->z * other;
		return temp;
	}


	inline Vec3 Vec3::operator/(const float &other)
	{
		Vec3 temp;
		temp.x = this->x / other;
		temp.y = this->y / other;
		temp.z = this->z / other;
		return temp;
	}
	//------------------------------------------------------------------------------------------//

	inline Vec3 Vec3::operator*(const float &&other)
	{
		Vec3 temp;
		temp.x = this->x * other;
		temp.y = this->y * other;
		temp.z = this->z * other;
		return temp;
	}


	inline Vec3 Vec3::operator/(const float &&other)
	{
		Vec3 temp;
		temp.x = this->x / other;
		temp.y = this->y / other;
		temp.z = this->z / other;
		return temp;
	}
	//------------------------------------------------------------------------------------------//

	inline void Vec3::operator*=(const float &other)
	{
		this->x = this->x * other;
		this->y = this->y * other;
		this->z = this->z * other;
	}


	inline void Vec3::operator/=(const float &other)
	{
		this->x = this->x / other;
		this->y = this->y / other;
		this->z = this->z / other;
	}
	//------------------------------------------------------------------------------------------//

	inline void Vec3::operator*=(const float &&other)
	{
		this->x = this->x * other;
		this->y = this->y * other;
		this->z = this->z * other;
	}


	inline void Vec3::operator/=(const float &&other)
	{
		this->x = this->x / other;
		this->y = this->y / other;
		this->z = this->z / other;
	}
	//------------------------------------------------------------------------------------------//

	//------------------------------------------------------------------------------------------//
	// Non-Member Operator Overloads
	//------------------------------------------------------------------------------------------//
	inline Vec3 operator*(const float &scalar, const Vec3 &vec)
	{
		return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	inline Vec3 operator/(const float &scalar, const Vec3 &vec)
	{
		return Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
	}

	inline Vec3 operator+(const Vec3 &a, const Vec3 &b)
	{
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	inline Vec3 operator-(const Vec3 &a, const Vec3 &b)
	{
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
}
