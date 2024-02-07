#include "../../include/shapes/baseshape.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <algorithm>
#include <memory>
#include <vector>


BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices)
	: x(x), y(y) {

	this->vbo = std::make_unique<VBO>();
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	

	// this->vbo = new VBO();
	// this->ebo = new EBO(indices);
	// this->shader = new ShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);
}

BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const Color& color, const int vertices_count)
	: x(x), y(y) {

	// This is important in case of a square
	std::vector<float> colors(vertices_count * 3, 0.0f); 
	for(int i = 0; i < vertices_count; i++) {
		auto it = colors.begin() + (i * 3); // Calculate the insertion position for this vertex
		colors.insert(it, { color.r, color.g, color.b }); // Insert the color components
	}

	this->vbo = std::make_unique<VBO>(colors);
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	

	// this->vbo = new VBO(colors);
	// this->ebo = new EBO(indices);
	// this->shader = new ShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);
	
}

BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors)
	: x(x), y(y) {

	this->vbo = std::make_unique<VBO>(colors);
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	

	// this->vbo = new VBO(colors);
	// this->ebo = new EBO(indices);
	// this->shader = new ShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);
}


