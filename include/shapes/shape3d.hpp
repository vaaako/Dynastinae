#pragma once

#include "shape.hpp"

struct Shape3D : Shape {
	Shape3D() = default;
	Shape3D(const vec3<float>& position, const vec2<float>& size, const float rotate);
};
