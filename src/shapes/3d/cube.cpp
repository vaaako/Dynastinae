#include "../../../include/shapes/3d/cube.hpp"


Cube::Cube() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Cube::Cube(const float x, const float y, const float z, const float width, const float height, const float rotate)
	: Shape3D(x, y, z, width, height, rotate) {
}

Cube::Cube(const glm::vec3 position, const glm::vec2 size, const float rotate)
	: Shape3D(position, size, rotate) {
}
