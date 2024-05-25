#include "../../../include/shapes/2d/triangle.hpp"

Triangle::Triangle() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Triangle::Triangle(const vec2<float>& position, const vec2<float>& size, const float rotate)
	: Shape2D(position, size, rotate) {}
