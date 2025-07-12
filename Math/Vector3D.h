#pragma once

namespace Math
{
	struct Vector3D
	{
		union { float x, r; };
		union { float y, g; };
		union { float z, b; };


		Vector3D(float val) :x(val), y(val), z(val) {}
		explicit Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) :x(x), y(y), z(z) {}


		Vector3D& operator=(const Vector3D& source);
		Vector3D& operator+=(const Vector3D& v2);
		Vector3D& operator-=(const Vector3D& v2);
	};

	// Vector assignation
	inline Vector3D& Vector3D::operator=(const Vector3D& source)
	{
		x = source.x;
		y = source.y;
		z = source.z;
		return *this;
	}

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