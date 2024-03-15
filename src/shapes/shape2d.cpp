#include "../../include/shapes/shape2d.hpp"

Shape2D::Shape2D(const float x, const float y, const float width, const float height, const float rotate)
	: Shape(Vector3f(x, y, 0.0f), Vector2f(width, height), rotate) {}

Shape2D::Shape2D(const Vector2f position, const Vector2f size, const float rotate)
	: Shape(Vector3f(position.x, position.y, 0.0f), size, rotate) {}
