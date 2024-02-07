#include "../../include/shapes/baseshape.hpp"


BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors)
	: x(x), y(y) {


	this->vao = new VAO();
	this->vbo = new VBO(colors);
	this->ebo = new EBO(indices);
	this->shader = new ShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);	
}

