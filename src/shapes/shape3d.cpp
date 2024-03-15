#include "../../include/shapes/shape3d.hpp"

Shape3D::Shape3D(const float x, const float y, const float z, const float width, const float height, const float rotate)
	: Shape(Vector3f(x, y, z), Vector2f(width, height), rotate) {}

Shape3D::Shape3D(const Vector3f position, const Vector2f size, const float rotate) : Shape(position, size, rotate) {}


