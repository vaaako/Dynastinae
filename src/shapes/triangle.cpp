#include "../../include/shapes/triangle.hpp"

Triangle::Triangle(const float x, const float y, const float width, const float height) {
	// Define the vertices and indices for a 2D triangle
	const std::vector<float> vertices = {
		// x,                y,          0.0f,
		// x + width,        y,          0.0f,
		// x + width * 0.5f, y + height, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	const std::vector<float> colors = {
		1.0f, 0.0f, 0.0f, // Bottom Right
		0.0f, 1.0f, 0.0f, // Bottom Left
		0.0f, 0.0f, 1.0f  // Top
	};

	const std::vector<unsigned int> indices = {
		0, 1, 2
	};

	this->vao = new VAO();
	this->vbo = new VBO(vertices, colors);
	this->ebo = new EBO(indices);
	this->shader = new ShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);
}
