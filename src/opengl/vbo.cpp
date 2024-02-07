#include "../../include/opengl/vbo.hpp"

VBO::VBO() {}

VBO::VBO(const std::vector<float>& data) {
	this->store_data(1, 3, data);
}

VBO::VBO(const std::vector<float>& vertices, const std::vector<float>& color) {
	this->store_data(0, 3, vertices);
	this->store_data(1, 3, color);
}

void VBO::store_data(const unsigned int position, const unsigned int dimensions, const std::vector<float>& data) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	// Configure the Vertex Attribute so OpenGl knows how to read the VBO
	glVertexAttribPointer(position, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
	//                                          kind,          amount, offset (where array starts)

	glEnableVertexAttribArray(position); // Enabling Vertex Position to draw
	glBindBuffer(GL_ARRAY_BUFFER, this->id);   // Unbind VBO
}


// IF WAS THE SAME ARRAY //
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(0); // Enabling

// // color attribute
// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
// glEnableVertexAttribArray(1);
// IF WAS THE SAME ARRAY //
