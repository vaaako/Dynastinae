#include "../../include/opengl/ebo.hpp"

EBO::EBO(const std::vector<unsigned int>& indices) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}


EBO::EBO(const std::vector<unsigned int>& indices, const std::vector<unsigned int>& indices2) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	// Bytes size
	const GLuint indices_size = indices.size() * sizeof(unsigned int);
	const GLuint indices2_size = indices2.size() * sizeof(unsigned int);
	const GLuint total_size = indices_size + indices2_size;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, total_size, nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices_size, indices.data());
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices2_size, indices2.data()); // Starting on end of data1
}
