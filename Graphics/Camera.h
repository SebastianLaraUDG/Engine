#pragma once
#include "Math/Vector3D.h"

using Math::Vector3D;

class Camera
{
public:
	Camera();
	Camera(Vector3D location);
	
	inline Vector3D GetLocation() const { return location; }
	inline void SetLocation(const Vector3D loc) { location = loc; }
private:
	Vector3D location;
};