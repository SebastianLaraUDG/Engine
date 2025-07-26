#pragma once
#include "Vector4D.h"
#include "Vector3D.h"

namespace Math
{
	constexpr float DEG2RAD = 3.14159265f / 180.0f;

	/*
	* ROW-MAJOR
	* It is advised to first do scaling operations,
	then rotations and lastly translations when
	combining matrices otherwise they may
	(negatively) affect each other.
	*/
	struct Matrix4D
	{
		float r0c0, r0c1, r0c2, r0c3;
		float r1c0, r1c1, r1c2, r1c3;
		float r2c0, r2c1, r2c2, r2c3;
		float r3c0, r3c1, r3c2, r3c3;

		inline Matrix4D();
		inline explicit Matrix4D(
			float _r0c0, float _r0c1, float _r0c2, float _r0c3,
			float _r1c0, float _r1c1, float _r1c2, float _r1c3,
			float _r2c0, float _r2c1, float _r2c2, float _r2c3,
			float _r3c0, float _r3c1, float _r3c2, float _r3c3);
		// glm::mat4(1.0f);
		inline static Matrix4D Identity();

		/// <summary>
		/// Returns a new 4x4 matrix representing the original matrix translated by the given 3D vector.
		/// </summary>
		/// <param name="mat">The original 4x4 transformation matrix.</param>
		/// <param name="vec3">The 3D vector specifying the translation.</param>
		/// <returns>A new Matrix4D that is the result of applying the translation to the input matrix.</returns>
		inline static Matrix4D Translate(const Matrix4D& mat, const Vector3D& vec3);

		/// <summary>
		/// Creates a rotation matrix with the angle provided around the specified axis.
		/// </summary>
		/// <param name="mat">The matrix to transform</param>
		/// <param name="angle">The magnitude of rotation IN RADIANS</param>
		/// <param name="axis">Specifies the axis to rotate around. (Should be a unit vector)</param>
		/// <returns></returns>
		inline static Matrix4D Rotate(const Matrix4D& mat, const float& angle, Vector3D axis);

		/// <summary>
		/// Scales a 4D matrix by a 3D scale vector.
		/// </summary>
		/// <param name="mat">The input 4D matrix to be scaled.</param>
		/// <param name="scaleVec">The 3D vector specifying the scale factors along each axis.</param>
		/// <returns>A new 4D matrix resulting from scaling the input matrix by the given scale vector.</returns>
		inline static Matrix4D Scale(const Matrix4D& mat, const Vector3D& scaleVec);

		/// <summary>
		/// Builds a perspective projection matrix.
		/// </summary>
		/// <param name="FOV">The field of view in radians.</param>
		/// <param name="aspectRatio">The aspect ratio (width/height).</param>
		/// <param name="near">The near plane of the perspective frustum. All the objects
		/// in front of the near plane will not be drawn</param>
		/// <param name="far">The far plane of the perspective frustum. All the objects
		/// behind the far plane will not be drawn</param>
		/// <returns>A perspective projection matrix</returns>
		inline static Matrix4D Perspective(const float& FOV, const float& aspectRatio, const float& near, const float& far);

		/// <summary>
		/// Creates a view transformation matrix representing a way that the user
		/// looks at a target from a position
		/// </summary>
		/// <param name="position">Position of camera in world coordinates</param>
		/// <param name="target">The target position/direction we should look at</param>
		/// <param name="up">Up vector of global world</param>
		/// <returns>A view transformation matrix representing a way that the user
		/// looks at a target from a position.
		/// </returns>
		inline static Matrix4D LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up = Vector3D(0.0f, 1.0f, 0.0f));


		inline Vector4D operator*(const Vector4D& vec4) const;
		inline Matrix4D operator*(const Matrix4D& otherMat) const;
	};

	Matrix4D::Matrix4D() : r0c0(0.0f), r0c1(0.0f), r0c2(0.0f), r0c3(0.0f),
		r1c0(0.0f), r1c1(0.0f), r1c2(0.0f), r1c3(0.0f),
		r2c0(0.0f), r2c1(0.0f), r2c2(0.0f), r2c3(0.0f),
		r3c0(0.0f), r3c1(0.0f), r3c2(0.0f), r3c3(0.0f)
	{
	}

	Matrix4D::Matrix4D(float _r0c0, float _r0c1, float _r0c2, float _r0c3,
		float _r1c0, float _r1c1, float _r1c2, float _r1c3,
		float _r2c0, float _r2c1, float _r2c2, float _r2c3,
		float _r3c0, float _r3c1, float _r3c2, float _r3c3)
		: r0c0(_r0c0), r0c1(_r0c1), r0c2(_r0c2), r0c3(_r0c3),
		r1c0(_r1c0), r1c1(_r1c1), r1c2(_r1c2), r1c3(_r1c3),
		r2c0(_r2c0), r2c1(_r2c1), r2c2(_r2c2), r2c3(_r2c3),
		r3c0(_r3c0), r3c1(_r3c1), r3c2(_r3c2), r3c3(_r3c3)
	{
	}

	inline Matrix4D Matrix4D::Identity()
	{
		return Matrix4D(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4D Matrix4D::Translate(const Matrix4D& mat, const Vector3D& vec3)
	{
		Matrix4D result = Identity();
		result.r0c3 = vec3.x;
		result.r1c3 = vec3.y;
		result.r2c3 = vec3.z;
		return mat * result;
	}

	Matrix4D Matrix4D::Rotate(const Matrix4D& mat, const float& angle, Vector3D axis)
	{
		// Based on Rodrigues's rotation formula
		// https://www.cis.upenn.edu/~cis580/Spring2015/Lectures/cis580-08-Quaternion_lecture.pdf
		// Page 19

		// First of all, ensure axis is a unit vector (normalized)
		axis = axis.Normalized();

		Matrix4D result;
		const float c = cos(angle);
		const float s = sin(angle);
		const float oneMinusC = 1.0f - c;

		result.r0c0 = axis.x * axis.x + (1.0f - axis.x * axis.x) * c;
		result.r0c1 = axis.x * axis.y * oneMinusC - axis.z * s;
		result.r0c2 = axis.x * axis.z * oneMinusC + axis.y * s;

		result.r1c0 = axis.x * axis.y * oneMinusC + axis.z * s;
		result.r1c1 = axis.y * axis.y + (1.0f - axis.y * axis.y) * c;
		result.r1c2 = axis.y * axis.z * oneMinusC - axis.x * s;

		result.r2c0 = axis.x * axis.z * oneMinusC - axis.y * s;
		result.r2c1 = axis.y * axis.z * oneMinusC + axis.x * s;
		result.r2c2 = axis.z * axis.z + (1.0f - axis.z * axis.z) * c;

		result.r3c3 = 1.0f;

		return mat * result;
	}

	Matrix4D Matrix4D::Scale(const Matrix4D& mat, const Vector3D& scaleVector)
	{
		Matrix4D result = Identity();
		result.r0c0 = scaleVector.x;
		result.r1c1 = scaleVector.y;
		result.r2c2 = scaleVector.z;
		return mat * result;
	}

	Matrix4D Matrix4D::Perspective(const float& FOV, const float& aspectRatio, const float& near, const float& far)
	{
		Matrix4D result;

		result.r0c0 = 1.0f / (aspectRatio * tan(FOV / 2.0f));
		result.r1c1 = 1.0f / tan(FOV / 2.0f);
		result.r2c2 = -((far + near) / (far - near));
		result.r2c3 = -(2.0f * far * near) / (far - near);
		result.r3c2 = -1.0f;
		return result;
	}

	Matrix4D Matrix4D::LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up)
	{

		Matrix4D rotationMatrix;

		// Direction or 'forward'
		// The camera looks INTO the negative Z - axis.
		// So, the direction vector for the world's Z-axis from the camera's perspective
		// is from the target to the position.
		const Vector3D Dir = (position - target).Normalized();

		const Vector3D Right = Vector3D::CrossProduct(up, Dir).Normalized();
		// This calculates the camera's local Y-axis, ensuring it's orthogonal to Dir and Right.
		const Vector3D Up = Vector3D::CrossProduct(Dir, Right).Normalized();


		rotationMatrix.r0c0 = Right.x;
		rotationMatrix.r0c1 = Right.y;
		rotationMatrix.r0c2 = Right.z;
		rotationMatrix.r1c0 = Up.x;
		rotationMatrix.r1c1 = Up.y;
		rotationMatrix.r1c2 = Up.z;
		rotationMatrix.r2c0 = Dir.x;
		rotationMatrix.r2c1 = Dir.y;
		rotationMatrix.r2c2 = Dir.z;
		rotationMatrix.r3c3 = 1.0f;

		Matrix4D translationMatrix = Identity();
		translationMatrix.r0c3 = -position.x;
		translationMatrix.r1c3 = -position.y;
		translationMatrix.r2c3 = -position.z;

		return rotationMatrix * translationMatrix;
	}

	Vector4D Matrix4D::operator*(const Vector4D& vec4) const
	{
		Vector4D result{};

		result.x = r0c0 * vec4.x + r0c1 * vec4.y + r0c2 * vec4.z + r0c3 * vec4.w;
		result.y = r1c0 * vec4.x + r1c1 * vec4.y + r1c2 * vec4.z + r1c3 * vec4.w;
		result.z = r2c0 * vec4.x + r2c1 * vec4.y + r2c2 * vec4.z + r2c3 * vec4.w;
		result.w = r3c0 * vec4.x + r3c1 * vec4.y + r3c2 * vec4.z + r3c3 * vec4.w;
		return result;
	}

	Matrix4D Matrix4D::operator*(const Matrix4D& other) const
	{
		Matrix4D result;

		result.r0c0 = r0c0 * other.r0c0 + r0c1 * other.r1c0 + r0c2 * other.r2c0 + r0c3 * other.r3c0;
		result.r0c1 = r0c0 * other.r0c1 + r0c1 * other.r1c1 + r0c2 * other.r2c1 + r0c3 * other.r3c1;
		result.r0c2 = r0c0 * other.r0c2 + r0c1 * other.r1c2 + r0c2 * other.r2c2 + r0c3 * other.r3c2;
		result.r0c3 = r0c0 * other.r0c3 + r0c1 * other.r1c3 + r0c2 * other.r2c3 + r0c3 * other.r3c3;

		result.r1c0 = r1c0 * other.r0c0 + r1c1 * other.r1c0 + r1c2 * other.r2c0 + r1c3 * other.r3c0;
		result.r1c1 = r1c0 * other.r0c1 + r1c1 * other.r1c1 + r1c2 * other.r2c1 + r1c3 * other.r3c1;
		result.r1c2 = r1c0 * other.r0c2 + r1c1 * other.r1c2 + r1c2 * other.r2c2 + r1c3 * other.r3c2;
		result.r1c3 = r1c0 * other.r0c3 + r1c1 * other.r1c3 + r1c2 * other.r2c3 + r1c3 * other.r3c3;

		result.r2c0 = r2c0 * other.r0c0 + r2c1 * other.r1c0 + r2c2 * other.r2c0 + r2c3 * other.r3c0;
		result.r2c1 = r2c0 * other.r0c1 + r2c1 * other.r1c1 + r2c2 * other.r2c1 + r2c3 * other.r3c1;
		result.r2c2 = r2c0 * other.r0c2 + r2c1 * other.r1c2 + r2c2 * other.r2c2 + r2c3 * other.r3c2;
		result.r2c3 = r2c0 * other.r0c3 + r2c1 * other.r1c3 + r2c2 * other.r2c3 + r2c3 * other.r3c3;

		result.r3c0 = r3c0 * other.r0c0 + r3c1 * other.r1c0 + r3c2 * other.r2c0 + r3c3 * other.r3c0;
		result.r3c1 = r3c0 * other.r0c1 + r3c1 * other.r1c1 + r3c2 * other.r2c1 + r3c3 * other.r3c1;
		result.r3c2 = r3c0 * other.r0c2 + r3c1 * other.r1c2 + r3c2 * other.r2c2 + r3c3 * other.r3c2;
		result.r3c3 = r3c0 * other.r0c3 + r3c1 * other.r1c3 + r3c2 * other.r2c3 + r3c3 * other.r3c3;

		return result;
	}
}