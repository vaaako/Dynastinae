#pragma once

#include "Dynastinae/shapes/shape2d.hpp"

// NOTE -- Technically I could use only one VAO for Triangle and Rectangle

struct Rectangle : Shape2D {
	std::vector<float> vertices = {
		// VERTICES / TEXTURE
		0.0f, 0.0f,   1.0f, 1.0f, // Bottom Left
		1.0f, 0.0f,   0.0f, 1.0f, // Bottom Right
		1.0f, 1.0f,   0.0f, 0.0f, // Top Right
		0.0f, 1.0f,   1.0f, 0.0f  // Top Left
	};

	const std::vector<uint32> indices = {
		0, 1, 2, // First triangle
		2, 3, 0  // Second triangle
	};

	Rectangle();
	Rectangle(const vec2<float>& position, const vec2<float>& size, const float rotate = 0.0f);
};
