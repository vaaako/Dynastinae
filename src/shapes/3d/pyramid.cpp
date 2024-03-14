#include "../../../include/shapes/3d/pyramid.hpp"


Pyramid::Pyramid() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Pyramid::Pyramid(const float x, const float y, const float z, const float width, const float height, const float rotate)
	: Shape3D(x, y, z, width, height, rotate) {}

Pyramid::Pyramid(const glm::vec3 position, const glm::vec2 size, const float rotate)
	: Shape3D(position, size, rotate) {}
