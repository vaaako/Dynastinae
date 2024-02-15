#include "../../include/shapes/baseshape.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <memory>
#include <vector>

/**
 * NO COLOR */
BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices)
	: x(x), y(y), indices_size(static_cast<unsigned int>(indices.size())) {

	this->vbo = std::make_unique<VBO>();
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	
}


/**
 * COLOR ARRAY */
BaseShape::BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors)
	: x(x), y(y), indices_size(static_cast<unsigned int>(indices.size())) {

	this->vbo = std::make_unique<VBO>(colors, 1, 4);
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	
}
