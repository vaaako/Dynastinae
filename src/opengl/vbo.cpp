#include "../../include/opengl/vbo.hpp"

#define INT2VOID(v) (void*)(uintptr_t)(v)

VBO::VBO() {
	glGenBuffers(1, &this->id);
}


void VBO::store_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimension, const unsigned int total_dimensions, const void* offset) {
	this->bind();

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(position, dimension, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), offset);
	glEnableVertexAttribArray(position);

	this->unbind();
}

void VBO::link_attrib(const unsigned int position, const unsigned int dimension, const unsigned int total_dimensions, const void* offset) {
	this->bind();
	glVertexAttribPointer(position, dimension, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), offset);
	glEnableVertexAttribArray(position);
	this->unbind();

}

void VBO::store_two_fields_data(const std::vector<float>& data, const unsigned int pos_dim, const unsigned int tex_dim, const unsigned int vertex1, const unsigned int vertex2) {
	const int dimensions_bytes = (pos_dim + tex_dim) * sizeof(float);

	this->bind();

	// Allocate Memory
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	// Seet Data Vertex Attribute
	glVertexAttribPointer(vertex1, pos_dim, GL_FLOAT, GL_FALSE, dimensions_bytes, (void*)0); // Position attribute
	glEnableVertexAttribArray(vertex1);
	// Texture coordinate
	glVertexAttribPointer(vertex2, tex_dim, GL_FLOAT, GL_FALSE, dimensions_bytes, (void*)(pos_dim * sizeof(float))); // Texture coords
	glEnableVertexAttribArray(vertex2);

	this->unbind();
}
