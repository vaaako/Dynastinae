#include "../../../include/shapes/2d/triangle.hpp"

Triangle::Triangle() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Triangle::Triangle(const float x, const float y, const float width, const float height, const float rotate)
	: Shape2D(x, y, width, height, rotate) {}

Triangle::Triangle(const Vector2f position, const Vector2f size, const float rotate)
	: Shape2D(position, size, rotate) {}
