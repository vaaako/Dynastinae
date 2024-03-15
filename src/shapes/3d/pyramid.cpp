#include "../../../include/shapes/3d/pyramid.hpp"


Pyramid::Pyramid() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Pyramid::Pyramid(const float x, const float y, const float z, const float rotate)
	: Shape3D(x, y, z, 0.0f, 0.0f, rotate) {}

Pyramid::Pyramid(const Vector3f position, const float rotate)
	: Shape3D(position, { 0.0f, 0.0f }, rotate) {}
