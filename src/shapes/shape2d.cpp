#include "../../include/shapes/shape2d.hpp"
#include <glm/ext/vector_float3.hpp>

Shape2D::Shape2D(const float x, const float y, const float width, const float height, const float rotate)
	: Shape(glm::vec3(x, y, 0.0f), glm::vec2(width, height), rotate) {}

Shape2D::Shape2D(const glm::vec2 position, const glm::vec2 size, const float rotate)
	: Shape(glm::vec3(position.x, position.y, 0.0f), size, rotate) {}
