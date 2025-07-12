#pragma once
#include "Vector3D.h"

namespace Math
{
	struct Matrix3D
	{
		float r0c0, r0c1, r0c2;
		float r1c0, r1c1, r1c2;
		float r2c0, r2c1, r2c2;

		Matrix3D() : r0c0(0.0f), r0c1(0.0f), r0c2(0.0f),
			r1c0(0.0f), r1c1(0.0f), r1c2(0.0f),
			r2c0(0.0f), r2c1(0.0f), r2c2(0.0f) {
		}

	};
	inline Vector3D operator*(const Matrix3D& matrix, const Vector3D& vec)
	{
		Vector3D result;
		result.x = matrix.r0c0 * vec.x + matrix.r0c1 * vec.y + matrix.r0c2 * vec.z;
		result.y = matrix.r1c0 * vec.x + matrix.r1c1 * vec.y + matrix.r1c2 * vec.z;
		result.z = matrix.r2c0 * vec.x + matrix.r2c1 * vec.y + matrix.r2c2 * vec.z;
		return result;
	}
}