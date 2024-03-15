#pragma once

#include "../shape3d.hpp"

struct Pyramid : Shape3D {
	// Vertices: 12 / 16 (with base)
	const std::vector<float> vertices = {
		// VERTICES         /   TEXTURE
		// Front face
		 0.0f,  1.0f, 0.0f,   0.5f, 1.0f, // Top vertex
		-1.0f, -1.0f, 1.0f,   0.0f, 0.0f, // Bottom left vertex
		 1.0f, -1.0f, 1.0f,   1.0f, 0.0f, // Bottom right vertex

		// Right face
		0.0f,  1.0f,  0.0f,   0.5f, 1.0f, // Top vertex
		1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // Bottom left vertex
		1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // Bottom right vertex

		// Back face
		 0.0f,  1.0f,  0.0f,   0.5f, 1.0f, // Top vertex
		 1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Bottom left vertex
		-1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // Bottom right vertex

		// Left face
		 0.0f,  1.0f,  0.0f,   0.5f, 1.0f, // Top vertex
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Bottom left vertex
		-1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // Bottom right vertex

		// Bottom face
		-1.0f, -1.0f,  1.0f,   0.0f, 1.0f, // Bottom left vertex
		 1.0f, -1.0f,  1.0f,   1.0f, 1.0f, // Bottom right vertex
		 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // Top right vertex
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Top left vertex
	};

	const std::vector<unsigned int> indices = {
		0, 1, 2,   // Front face
		3, 4, 5,   // Right face
		6, 7, 8,   // Back face
		9, 10, 11, // Left face
		// Base
		12, 13, 14,
		12, 14, 15
	};

	Pyramid();
	Pyramid(const float x, const float y, const float z, const float rotate = 0.0f);
	Pyramid(const Vector3f position, const float rotate = 0.0f);
};
