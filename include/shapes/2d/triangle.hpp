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

	const std::vector<uint32> indices = {
		0, 1, 2
	};

	Triangle();
	Triangle(const vec2<float>& position, const vec2<float>& size, const float rotate = 0.0f);
};
