#include "Dynastinae/opengl/vbo.hpp"

#define INT2VOID(v) (void*)(uintptr_t)(v)

VBO::VBO() {
	glGenBuffers(1, &this->id);
}


void VBO::store_data(const std::vector<float>& data, const uint32 position, const uint32 dimension, const uint32 total_dimensions, const void* offset) {
	this->bind();

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(position, dimension, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(total_dimensions * sizeof(float)), offset);
	glEnableVertexAttribArray(position);

	this->unbind();
}

void VBO::link_attrib(const uint32 position, const uint32 dimension, const uint32 total_dimensions, const void* offset) {
	this->bind();
	glVertexAttribPointer(position, dimension, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(total_dimensions * sizeof(float)), offset);
	glEnableVertexAttribArray(position);
	this->unbind();

}

void VBO::store_two_fields_data(const std::vector<float>& data, const uint32 pos_dim, const uint32 tex_dim, const uint32 vertex1, const uint32 vertex2) {
	const GLsizei dimensions_bytes = static_cast<GLsizei>((pos_dim + tex_dim) * sizeof(float));

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
