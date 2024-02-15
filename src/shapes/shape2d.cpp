#include "../../include/shapes/shape2d.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

/**
 * NO COLOR */
Shape2D::Shape2D(const float x, const float y, const std::vector<unsigned int>& indices)
	: x(x), y(y), indices_size(static_cast<unsigned int>(indices.size())) {

	this->vbo = std::make_unique<VBO>();
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	
}


/**
 * COLOR ARRAY */
Shape2D::Shape2D(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors)
	: x(x), y(y), indices_size(static_cast<unsigned int>(indices.size())) {

	this->vbo = std::make_unique<VBO>(colors, 1, 4);
	this->ebo = std::make_unique<const EBO>(indices);
	this->shader = std::make_unique<const ShaderProgram>(this->vertexShaderSource, this->fragmentShaderSource);	
}
