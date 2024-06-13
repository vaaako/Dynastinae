#include "Dynastinae/shapes/2d/rectangle.hpp"
#include "Dynastinae/shapes/shape2d.hpp"

Rectangle::Rectangle()
	: Shape2D({
			// VERTICES / TEXTURE
			0.0f, 0.0f,   1.0f, 1.0f, // Bottom Left
			1.0f, 0.0f,   0.0f, 1.0f, // Bottom Right
			1.0f, 1.0f,   0.0f, 0.0f, // Top Right
			0.0f, 1.0f,   1.0f, 0.0f  // Top Left
		},
		{
			0, 1, 2, // First triangle
			2, 3, 0  // Second triangle
		}) {}

