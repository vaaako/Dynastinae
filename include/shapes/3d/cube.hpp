#pragma once

#include "../shape3d.hpp"

struct Cube : Shape3D {
	// Vertices: 24
	std::vector<float> vertices = {
		// VERTICES         /   TEXTURE
		// Front face
		-1.0f, -1.0f, 1.0f,   0.0f, 0.0f, // Bottom left vertex
		 1.0f, -1.0f, 1.0f,   1.0f, 0.0f, // Bottom right vertex
		 1.0f,  1.0f, 1.0f,   1.0f, 1.0f, // Top right vertex
		-1.0f,  1.0f, 1.0f,   0.0f, 1.0f, // Top left vertex

		// Back face
		-1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // 4
		-1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // 5
		 1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // 6
		 1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // 7
		
		// Top face
		-1.0f, 1.0f, -1.0f,   0.0f, 1.0f, // 8
		-1.0f, 1.0f,  1.0f,   0.0f, 0.0f, // 9
		 1.0f, 1.0f,  1.0f,   1.0f, 0.0f, // 10
		 1.0f, 1.0f, -1.0f,   1.0f, 1.0f, // 11
		
		// Bottom face
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // 12
		 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // 13
		 1.0f, -1.0f,  1.0f,   1.0f, 1.0f, // 14
		-1.0f, -1.0f,  1.0f,   0.0f, 1.0f, // 15
		
		// Right face
		1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // 16
		1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // 17
		1.0f,  1.0f,  1.0f,   0.0f, 1.0f, // 18
		1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // 19
		
		// Left face
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // 20
		-1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // 21
		-1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // 22
		-1.0f,  1.0f, -1.0f,   0.0f, 1.0f  // 23
	};

	std::vector<unsigned int> indices = {
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Back face
		4, 5, 6,
		4, 6, 7,

		// Top face
		8, 9, 10,
		8, 10, 11,

		// Bottom face
		12, 13, 14,
		12, 14, 15,

		// Right face
		16, 17, 18,
		16, 18, 19,

		// Left face
		20, 21, 22,
		20, 22, 23
	};

	Cube();
	Cube(const float x, const float y, const float z, const float rotate = 0.0f);
	Cube(const Vector3f position, const float rotate = 0.0f);
};
