#include "../../../include/shapes/2d/rectangle.hpp"

Rectangle::Rectangle() {
	this->set_vbo_and_ebo(this->vertices, this->indices);
}

Rectangle::Rectangle(const vec2<float>& position, const vec2<float>& size, const float rotate)
	: Shape2D(position, size, rotate) {}
