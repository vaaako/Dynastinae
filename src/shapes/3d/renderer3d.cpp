#include "../../../include/shapes/3d/renderer3d.hpp"

Renderer3D::Renderer3D(const float FOV, const float near_plane, const float far_plane)
	: fov(FOV), near_plane(near_plane), far_plane(far_plane) {
	// const std::vector<float> pyr_vert = {
	// 	// VERTICES       /     TEXTURE
	// 	0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 1
	// 	0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Vertex 2
	// 	1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Vertex 3
	// 	1.0f, 0.0f, 1.0f,   1.0f, 0.0f, // Vertex 4
	// 	0.5f, 0.8f, 0.5f,   0.5f, 1.0f  // Vertex 5 (Apex)
	// };

	const std::vector<float> pyr_vert = {
		-0.5f, 0.0f,  0.5f,   0.0f, 0.0f, // Vertex 1 (Base)
		-0.5f, 0.0f, -0.5f,   0.0f, 0.0f, // Vertex 2 (Base)
		 0.5f, 0.0f, -0.5f,   1.0f, 0.0f, // Vertex 3 (Base)
		 0.5f, 0.0f,  0.5f,   1.0f, 0.0f, // Vertex 4 (Base)
		 0.0f, 0.8f,  0.0f,   0.5f, 1.0f  // Vertex 5 (Apex)
	};


	// const std::vector<float> pyr_vert = {
	// 	1.0f, 0.0f, 0.0f,
	// 	1.0f, 0.0f, 1.0f,
	// 	0.0f, 0.0f, 1.0f,
	// 	0.0f, 0.0f, 0.0f,
	// 	0.0f, 0.5f, 0.0f,
	// };
	//
	const std::vector<unsigned int> indices = {
		0, 1, 2, // Triangle 1
		0, 2, 3, // Triangle 2
		0, 1, 4, // Triangle 3
		1, 2, 4, // Triangle 4
		2, 3, 4, // Triangle 5
		3, 0, 4  // Triangle 6
	};


	this->vbo = std::make_unique<VBO>();
	this->vbo->store_two_data(pyr_vert, 3, 2);
	// this->vbo = std::make_unique<VBO>(pyr_vert, 0, 3);

	this->ebo = std::make_unique<const EBO>(indices); // Since Rectangle indices starts with Triangle indices, I can upload only Rectangle indices
	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
}

