#pragma once

#include "shape.hpp"

struct Shape3D : Shape {
	// glm::vec3 position;

	Shape3D() = default;
	Shape3D(const float x, const float y, const float z,
		const float width, const float height, const float rotate);

	Shape3D(const glm::vec3 position, const glm::vec2 size, const float rotate);
};
