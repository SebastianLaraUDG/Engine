#pragma once

namespace Math
{
	struct Vector4D
	{
		union { float x, r; };
		union { float y, g; };
		union { float z, b; };
		union { float w, a; };
		
		Vector4D() = default;
		Vector4D(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};
		
	};
}