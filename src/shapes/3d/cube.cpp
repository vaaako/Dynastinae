#include "../../../include/shapes/3d/cube.hpp"


Cube::Cube() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Cube::Cube(const float x, const float y, const float z, const float rotate)
	: Shape3D(x, y, z, 0.0f, 0.0f, rotate) {
}

Cube::Cube(const Vector3f position, const float rotate)
	: Shape3D(position, { 0.0f, 0.0f }, rotate) {
}
