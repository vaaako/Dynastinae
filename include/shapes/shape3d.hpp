#pragma once

#include "shape.hpp"

struct Shape3D : Shape {
	Shape3D() = default;
	Shape3D(const float x, const float y, const float z,
		const float width, const float height, const float rotate);

	Shape3D(const Vector3f position, const Vector2f size, const float rotate);
};
