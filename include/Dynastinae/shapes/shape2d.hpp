#pragma once

#include "Dynastinae/shapes/shape.hpp"

struct Shape2D : Shape {
	std::vector<float> vertices;
	std::vector<uint32> indices;

	Shape2D() = default;
	Shape2D(const vec2<float>& position, const vec2<float>& size, const float rotate);

	inline void set_vbo(const std::vector<float>& vertices) override {
		this->vertices = vertices;
		this->vbo->store_two_fields_data(vertices, 2, 2);
	}
};
