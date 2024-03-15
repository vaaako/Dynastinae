#pragma once

#include "shape.hpp"

struct Shape2D : Shape {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Shape2D() = default;
	Shape2D(const float x, const float y, const float width, const float height, const float rotate);
	Shape2D(const Vector2f position, const Vector2f size, const float rotate);

	inline void set_vbo(const std::vector<float>& vertices) override {
		this->vertices = vertices;
		this->vbo->store_two_fields_data(vertices, 2, 2);
	}
};
