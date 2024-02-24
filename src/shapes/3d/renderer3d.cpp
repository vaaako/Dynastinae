#include "../../../include/shapes/3d/renderer3d.hpp"

Renderer3D::Renderer3D(const float FOV, const float near_plane, const float far_plane)
	: fov(FOV), near_plane(near_plane), far_plane(far_plane) {


	/**
	 * PYRAMID
	 * */
	// Vertices: 12 / 16 (with base)
	const std::vector<float> pyramid_vertices = {
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

	const std::vector<unsigned int> pyramid_indices = {
		0, 1, 2,   // Front face
		3, 4, 5,   // Right face
		6, 7, 8,   // Back face
		9, 10, 11, // Left face
		// Base
		12, 13, 14,
		12, 14, 15
	};



	/**
	 * CUBE
	 * */
	// Vertices: 24
	const std::vector<float> cube_vertices = {
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

	const std::vector<float> cube_texture = {
		// Front face
		0.0f, 0.0f, // Bottom left vertex
		1.0f, 0.0f, // Bottom right vertex
		1.0f, 1.0f, // Top right vertex
		0.0f, 1.0f, // Top left vertex

		// Back face
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		// Top face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		// Bottom face
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		// Right face
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		// Left face
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	const std::vector<unsigned int> cube_indices = {
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

	// Store indices
	this->pyramid_indices_size = static_cast<int>(pyramid_indices.size());
	this->cube_indices_size    = static_cast<int>(cube_indices.size());

	// Store vertices and texture coordinates
	this->vbo = std::make_unique<VBO>();
	this->vbo->store_data(pyramid_vertices, cube_vertices, 3, 2);
	// this->vbo->store_data(cube_vertices, pyramid_vertices, 3, 2);

	// Store vertices
	this->ebo = std::make_unique<const EBO>(pyramid_indices, cube_indices);
	// this->ebo = std::make_unique<const EBO>(cube_indices, pyramid_indices);

	// Make shaders
	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
	this->shader_texture = std::make_unique<const ShaderProgram>(this->vertex_shader_texture, this->fragment_shader_texture);
}

