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
}

BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const Color& color, const int vertices_count)
	: x(x), y(y) {

	// This is important in case of a square
	const int dimension = 4; // RGBA
	std::vector<float> colors(vertices_count * dimension, 0.0f); 
	for(int i = 0; i < vertices_count; i++) {
		auto it = colors.begin() + (i * dimension);                // Calculate the insertion position for this vertex
		colors.insert(it, { color.r, color.g, color.b, color.a }); // Insert the color components
	}

	this->vbo = std::make_unique<VBO>(colors, 1, dimension);
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	
}

BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors)
	: x(x), y(y) {

	this->vbo = std::make_unique<VBO>(colors, 1, 4);
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	
}


