#include "../../include/shapes/shape3d.hpp"

Shape3D::Shape3D(const float x, const float y, const float z, const float width, const float height, const float rotate)
	: Shape(glm::vec3(x, y, z), glm::vec2(width, height), rotate) {}

Shape3D::Shape3D(const glm::vec3 position, const glm::vec2 size, const float rotate) : Shape(position, size, rotate) {}


