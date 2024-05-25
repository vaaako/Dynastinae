#include "../../../include/shapes/3d/pyramid.hpp"


Pyramid::Pyramid() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Pyramid::Pyramid(const vec3<float>& position, const float rotate)
	: Shape3D(position, { 0.0f, 0.0f }, rotate) {}
