#pragma once
#include <iostream>

namespace Math
{
	struct Vector3D
	{
		union { float x, r; };
		union { float y, g; };
		union { float z, b; };

		Vector3D() :x(0.0f), y(0.0f), z(0.0f) {}
		explicit Vector3D(float x, float y, float z) :x(x), y(y), z(z) {}

		inline float Magnitude() const;
		inline Vector3D Normalized() const;

		inline static Vector3D CrossProduct(const Vector3D& left, const Vector3D& right);
		inline static float DotProduct(const Vector3D& left, const Vector3D& right);

		/// <summary>
		/// Calculates the angle in radians between two 3D vectors.
		/// </summary>
		/// <param name="left">The first 3D vector.</param>
		/// <param name="right">The second 3D vector.</param>
		/// <returns>The angle in radians between the two vectors.</returns>
		inline static float Angle(const Vector3D& left, const Vector3D& right);

		//Vector3D& operator=(const Vector3D& source);
		Vector3D& operator+=(const Vector3D& v2);
		Vector3D& operator-=(const Vector3D& v2);
	};

	inline float Vector3D::Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3D Vector3D::Normalized() const
	{
		float magnitude = Magnitude();
		if (magnitude == 0.0f)
		{
			std::cout << "Vector has magnitude zero" << std::endl;
			return Vector3D(0.0f, 0.0f, 0.0f);
		}
		return Vector3D(x / magnitude, y / magnitude, z / magnitude);
	}

	Vector3D Vector3D::CrossProduct(const Vector3D& left, const Vector3D& right)
	{
		return Vector3D(
			left.y * right.z - right.y * left.z,
			left.z * right.x - right.z * left.x,
			left.x * right.y - right.x * left.y
		);
	}

	inline float Vector3D::DotProduct(const Vector3D& left, const Vector3D& right)
	{
		// NOTE: not tested yet
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	float Vector3D::Angle(const Vector3D& left, const Vector3D& right)
	{
		// NOTE: not tested yet
		const float dotP = DotProduct(left, right);

		return acos(dotP / (left.Magnitude() * right.Magnitude()));
	}

	/*
	// Vector assignment
	inline Vector3D& Vector3D::operator=(const Vector3D& source)
	{
		x = source.x;
		y = source.y;
		z = source.z;
		return *this;
	}
	*/


	// Vector addition
	inline Vector3D operator +(const Vector3D& v1, const Vector3D& v2)
	{
		return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	// Vector addition-assignation
	inline Vector3D& Vector3D::operator +=(const Vector3D& v2)
	{
		*this = *this + v2;
		return *this;
	}

	// Vector subtraction
	// a − b = el camino desde el final de b hasta el final de a
	inline Vector3D operator-(const Vector3D& v1, const Vector3D& v2)
	{
		return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	// Vector subtraction-assignation
	inline Vector3D& Vector3D::operator -=(const Vector3D& v2)
	{
		*this = *this - v2;
	}

	// Scaling a vector
	inline Vector3D operator*(float scalar, const Vector3D& vec)
	{
		return Vector3D(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
	// Scaling a vector
	inline Vector3D operator*(const Vector3D& vec, float scalar)
	{
		return scalar * vec;
	}
}