#pragma once
#include "Vector3D.h"
#include <cmath>


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

		Matrix3D(float _r0c0, float _r0c1, float _r0c2,
			float _r1c0, float _r1c1, float _r1c2,
			float _r2c0, float _r2c1, float _r2c2)
			: r0c0(_r0c0), r0c1(_r0c1), r0c2(_r0c2),
			r1c0(_r1c0), r1c1(_r1c1), r1c2(_r1c2),
			r2c0(_r2c0), r2c1(_r2c1), r2c2(_r2c2)
		{
		}

		static Matrix3D Identity();

		/// <summary>
		/// Creates a 3D rotation matrix representing a rotation around the X-axis by the specified angle.
		/// </summary>
		/// <param name="angle">The angle, in radians, to rotate around the X-axis.</param>
		/// <returns>A Matrix3D object representing the rotation around the X-axis by the given angle.</returns>
		inline static Matrix3D rotateX(float angle);


		/// <summary>
		/// Creates a 3D rotation matrix representing a rotation around the Y axis by the specified angle.
		/// </summary>
		/// <param name="angle">The angle of rotation in radians.</param>
		/// <returns>A Matrix3D object representing the rotation around the Y axis.</returns>
		inline static Matrix3D rotateY(float angle);

		/// <summary>
		/// Creates a 3D rotation matrix representing a rotation around the Z axis by the specified angle.
		/// </summary>
		/// <param name="angle">The angle, in radians, to rotate around the Z axis.</param>
		/// <returns>A 3D matrix representing the rotation around the Z axis by the given angle.</returns>
		inline static Matrix3D rotateZ(float angle);


		/// <summary>
		/// Creates a 3D rotation matrix representing a rotation around the X axis, the Y axis and the Z axis by the specified angle
		/// (in that order).
		/// </summary>
		/// <param name="angle">The angle, in radians, to rotate around</param>
		/// <returns>A 3D rotation matrix representing a rotation around the X axis, the Y axis and the Z axis by the specified angle.</returns>
		inline static Matrix3D rotate(float angle);


		inline Matrix3D operator*(const Matrix3D& other);
	};

	Matrix3D Matrix3D::Identity()
	{
		Matrix3D result =
		{
			1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,
			1.0f,0.0f,0.0f
		};
		return result;
	}

	inline Matrix3D Matrix3D::operator*(const Matrix3D& other)
	{
		Matrix3D result;

		// Producto de la fila 0 de la primera matriz por las columnas de la segunda matriz
		result.r0c0 = r0c0 * other.r0c0 + r0c1 * other.r1c0 + r0c2 * other.r2c0;
		result.r0c1 = r0c0 * other.r0c1 + r0c1 * other.r1c1 + r0c2 * other.r2c1;
		result.r0c2 = r0c0 * other.r0c2 + r0c1 * other.r1c2 + r0c2 * other.r2c2;

		// Producto de la fila 1 de la primera matriz por las columnas de la segunda matriz
		result.r1c0 = r1c0 * other.r0c0 + r1c1 * other.r1c0 + r1c2 * other.r2c0;
		result.r1c1 = r1c0 * other.r0c1 + r1c1 * other.r1c1 + r1c2 * other.r2c1;
		result.r1c2 = r1c0 * other.r0c2 + r1c1 * other.r1c2 + r1c2 * other.r2c2;

		// Producto de la fila 2 de la primera matriz por las columnas de la segunda matriz
		result.r2c0 = r2c0 * other.r0c0 + r2c1 * other.r1c0 + r2c2 * other.r2c0;
		result.r2c1 = r2c0 * other.r0c1 + r2c1 * other.r1c1 + r2c2 * other.r2c1;
		result.r2c2 = r2c0 * other.r0c2 + r2c1 * other.r1c2 + r2c2 * other.r2c2;

		return result;
	}

	inline Vector3D operator*(const Matrix3D& matrix, const Vector3D& vec)
	{

		return Vector3D(
			matrix.r0c0 * vec.x + matrix.r0c1 * vec.y + matrix.r0c2 * vec.z,
			matrix.r1c0 * vec.x + matrix.r1c1 * vec.y + matrix.r1c2 * vec.z,
			matrix.r2c0 * vec.x + matrix.r2c1 * vec.y + matrix.r2c2 * vec.z
		);
	}

	inline Matrix3D Matrix3D::rotateX(float angle)
	{
		Matrix3D result =
		{
			1.0f,	0.0f,		0.0f,
			0.0f,	cos(angle),	-sin(angle),
			0.0f,	sin(angle),	cos(angle)
		};
		return result;
	}

	inline Matrix3D Matrix3D::rotateY(float angle)
	{
		Matrix3D result =
		{
			cos(angle),	 0.0f,	sin(angle),
			0.0f,		 1.0f,	0.0f,
			-sin(angle), 0.0f,	cos(angle)
		};
		return result;
	}

	inline Matrix3D Matrix3D::rotateZ(float angle)
	{
		Matrix3D result =
		{
			cos(angle),	-sin(angle),	0.0f,
			sin(angle), cos(angle),		0.0f,
			0.0f,		0.0f,			1.0f
		};
		return result;
	}

	inline Matrix3D Matrix3D::rotate(float angle)
	{
		Matrix3D result = rotateX(angle) * rotateY(angle) * rotateZ(angle);
		return result;
	}

}