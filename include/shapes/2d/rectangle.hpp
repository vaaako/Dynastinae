#pragma once

#include "../shape2d.hpp"

// NOTE -- Technically I could use only one VAO for Triangle and Rectangle

struct Rectangle : Shape2D {
	std::vector<float> vertices = {
		// VERTICES / TEXTURE
		0.0f, 0.0f,   1.0f, 1.0f, // Bottom Left
		1.0f, 0.0f,   0.0f, 1.0f, // Bottom Right
		1.0f, 1.0f,   0.0f, 0.0f, // Top Right
		0.0f, 1.0f,   1.0f, 0.0f  // Top Left
	};

	const std::vector<unsigned int> indices = {
		0, 1, 2, // First triangle
		2, 3, 0  // Second triangle
	};

	Rectangle();
	Rectangle(const float x, const float y, const float width, const float height, const float rotate = 0.0f);
	Rectangle(const glm::vec2 position, const glm::vec2 size, const float rotate = 0.0f);
};
