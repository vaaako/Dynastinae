#include "../../include/opengl/vao.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &this->id);
	glBindVertexArray(this->id);
}