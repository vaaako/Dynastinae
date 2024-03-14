#pragma once

#include "shape.hpp"

struct Shape2D : Shape {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Shape2D();

	Shape2D(const float x, const float y, const float width, const float height, const float rotate);
	Shape2D(const glm::vec2 position, const glm::vec2 size, const float rotate);



	inline void set_vbo(const std::vector<float>& vertices) override {
		this->vertices = vertices;
		this->vbo->store_two_fields_data(vertices, 2, 2);
	}
};
