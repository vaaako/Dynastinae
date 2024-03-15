#pragma once

#include "../shape2d.hpp"

// NOTE -- Technically I could use only one VAO for Triangle and Rectangle

struct Triangle : Shape2D {
	std::vector<float> vertices = {
		// VERTICES / TEXTURE
		1.0f, 1.0f,   0.0f, 0.0f, // Bottom Right
		0.0f, 1.0f,   1.0f, 0.0f, // Bottom Left
		0.5f, 0.0f,   0.5f, 1.0f  // Middle
	};

	const std::vector<unsigned int> indices = {
		0, 1, 2
	};

	Triangle();
	Triangle(const float x, const float y, const float width, const float height, const float rotate = 0.0f);
	Triangle(const Vector2f position, const Vector2f size, const float rotate = 0.0f);
};
