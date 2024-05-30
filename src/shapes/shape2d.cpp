#include "Dynastinae/shapes/shape2d.hpp"

Shape2D::Shape2D(const vec2<float>& position, const vec2<float>& size, const float rotate)
	: Shape(vec3(position.x, position.y, 0.0f), size, rotate) {}
