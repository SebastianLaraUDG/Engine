#include "Camera.h"
#include "Middleware/GLFW/include/GLFW/glfw3.h"
#include "Math/Matrix4D.h"

Camera::Camera(Vector3D location, Vector3D up, Vector3D rotation) :
	front(Vector3D(0.0f, 0.0f, -1.0f))
{
	this->location = location;
	this->worldUp = up;
	this->rotation = rotation;
	UpdateCameraVectors();
}


void Camera::ProcessKeyboardInput(GLFWwindow* window, const float& deltaTime)
{
	float velocity = m_speed * deltaTime;

	// Movement keys
	// Forwards
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		location += front * velocity;
	// Backwards
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		location -= front * velocity;

	// Left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		location -= right * velocity;
	}
	// Right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		location += right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= m_mouseSensitivity;
	yOffset *= m_mouseSensitivity;

	rotation.y += xOffset;
	rotation.x += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped (clamp)
	if (constrainPitch)
	{
		if (rotation.x > 89.0f)
			rotation.x = 89.0f;
		if (rotation.x < -89.0f)
			rotation.x = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	zoom -= yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}


void Camera::UpdateCameraVectors()
{
	// calculate the new Front vector
	Vector3D Front;
	Front.x = cos(Math::DEG2RAD * rotation.y) * cos(Math::DEG2RAD * rotation.x);
	Front.y = sin(Math::DEG2RAD * rotation.x);
	Front.z = sin(Math::DEG2RAD * rotation.y) * cos(Math::DEG2RAD * rotation.x);
	this->front = Front.Normalized();
	// also re-calculate the Right and Up vector
	this->right = Vector3D::CrossProduct(this->front, worldUp).Normalized(); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = Vector3D::CrossProduct(right, front).Normalized();
}
