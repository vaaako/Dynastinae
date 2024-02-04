#include "../../include/opengl/ebo.hpp"

EBO::EBO(const std::vector<unsigned int>& indices) {
	glGenBuffers(1, &this->id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);
}