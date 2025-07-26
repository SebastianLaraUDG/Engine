#pragma once
#include "Math/Vector3D.h"
#include "Math/Matrix4D.h"

using Math::Vector3D;
using Math::Matrix4D;
struct GLFWwindow;

namespace CameraUtilities
{
	constexpr float YAW = -90.0f;
	constexpr float PITCH = 0.0f;
}

class Camera
{
public:

	Camera(Vector3D location = Vector3D(0.0f), Vector3D up = Vector3D(0.0f, 1.0f, 0.0f),
		Vector3D rotation = Vector3D(CameraUtilities::PITCH, CameraUtilities::YAW, 0.0f));

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	inline Matrix4D GetViewMatrix() const
	{
		return Matrix4D::LookAt(location, location + front, up);
	}

	inline Vector3D GetLocation() const { return location; }
	inline void SetLocation(const Vector3D loc) { location = loc; }

	inline Vector3D GetForwardVector() const { return front; }
	inline Vector3D GetUpVector() const { return up; }
	inline Vector3D GetRightVector() const { return right; }

	// Keyboard input
	void ProcessKeyboardInput(GLFWwindow* window, const float& deltaTime);

	void ProcessMouseMovement(float xOffset, float yOffset,
		bool constrainPitch = true);

	void ProcessMouseScroll(float yOffset);

private:
	Vector3D location;
	Vector3D front; // TODO: rename 'forward'?
	Vector3D up;
	Vector3D right;

	Vector3D worldUp; // TODO: static?

	Vector3D rotation; // x = pitch, y = yaw, z = roll.


	float m_speed = 5.0f;
	float m_mouseSensitivity = 0.1f;
	float zoom = 45.0f;

	// calculates the front vector from the Camera's (updated) Euler Angles
	void UpdateCameraVectors();
};