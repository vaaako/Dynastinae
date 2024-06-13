#include "Dynastinae/shapes/2d/triangle.hpp"

Triangle::Triangle()
	: Shape2D({
			// VERTICES / TEXTURE
			1.0f, 1.0f,   0.0f, 0.0f, // Bottom Right
			0.0f, 1.0f,   1.0f, 0.0f, // Bottom Left
			0.5f, 0.0f,   0.5f, 1.0f  // Middle
		},
		{
			0, 1, 2
		}) {}

