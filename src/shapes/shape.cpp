#include "../../include/shapes/shape.hpp"

Shape::Shape(const glm::vec3 position, const glm::vec2 size, const float rotate)
	: position(position), size(size), rotate(rotate) {}
