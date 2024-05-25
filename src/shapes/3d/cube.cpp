#include "../../../include/shapes/3d/cube.hpp"


Cube::Cube() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Cube::Cube(const vec3<float>& position, const float rotate)
	: Shape3D(position, { 0.0f, 0.0f }, rotate) {
}
