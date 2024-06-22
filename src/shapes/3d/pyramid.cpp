#include "Dynastinae/shapes/3d/pyramid.hpp"
#include "Dynastinae/shapes/shape3d.hpp"

Pyramid::Pyramid()
	: Shape3D({
		// Vertices: 12 / 16 (with base)
		// Front face
		Vertex { .position = glm::vec3( 0.0f,  1.0f, 0.0f), .texuv = glm::vec2(0.5f, 1.0f) }, // Top vertex
		Vertex { .position = glm::vec3(-1.0f, -1.0f, 1.0f), .texuv = glm::vec2(0.0f, 0.0f) }, // Bottom left vertex
		Vertex { .position = glm::vec3( 1.0f, -1.0f, 1.0f), .texuv = glm::vec2(1.0f, 0.0f) }, // Bottom right vertex

		// Right face
		Vertex { .position = glm::vec3(0.0f,  1.0f,  0.0f), .texuv = glm::vec2(0.5f, 1.0f) }, // Top vertex
		Vertex { .position = glm::vec3(1.0f, -1.0f,  1.0f), .texuv = glm::vec2(0.0f, 0.0f) }, // Bottom left vertex
		Vertex { .position = glm::vec3(1.0f, -1.0f, -1.0f), .texuv = glm::vec2(1.0f, 0.0f) }, // Bottom right vertex

		// Back face
		Vertex { .position = glm::vec3( 0.0f,  1.0f,  0.0f), .texuv = glm::vec2(0.5f, 1.0f) }, // Top vertex
		Vertex { .position = glm::vec3( 1.0f, -1.0f, -1.0f), .texuv = glm::vec2(0.0f, 0.0f) }, // Bottom left vertex
		Vertex { .position = glm::vec3(-1.0f, -1.0f, -1.0f), .texuv = glm::vec2(1.0f, 0.0f) }, // Bottom right vertex

		// Left face
		Vertex { .position = glm::vec3( 0.0f,  1.0f,  0.0f), .texuv = glm::vec2(0.5f, 1.0f) }, // Top vertex
		Vertex { .position = glm::vec3(-1.0f, -1.0f, -1.0f), .texuv = glm::vec2(0.0f, 0.0f) }, // Bottom left vertex
		Vertex { .position = glm::vec3(-1.0f, -1.0f,  1.0f), .texuv = glm::vec2(1.0f, 0.0f) }, // Bottom right vertex

		// Bottom face
		Vertex { .position = glm::vec3(-1.0f, -1.0f,  1.0f), .texuv = glm::vec2(0.0f, 1.0f) }, // Bottom left vertex
		Vertex { .position = glm::vec3( 1.0f, -1.0f,  1.0f), .texuv = glm::vec2(1.0f, 1.0f) }, // Bottom right vertex
		Vertex { .position = glm::vec3( 1.0f, -1.0f, -1.0f), .texuv = glm::vec2(1.0f, 0.0f) }, // Top right vertex
		Vertex { .position = glm::vec3(-1.0f, -1.0f, -1.0f), .texuv = glm::vec2(0.0f, 0.0f) }, // Top left vertex
	},
	{
		0, 1, 2,   // Front face
		3, 4, 5,   // Right face
		6, 7, 8,   // Back face
		9, 10, 11, // Left face
		// Base
		12, 13, 14,
		12, 14, 15
	}) {}

