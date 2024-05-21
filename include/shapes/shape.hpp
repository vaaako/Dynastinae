#pragma once

#include "../opengl/vbo.hpp"
#include "../opengl/vao.hpp"
#include "../opengl/ebo.hpp"
#include "../types/color.hpp"
#include "../types/texture.hpp"

#include <memory>

struct Shape {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	GLsizei indices_size = 0;

	// Safe delete
	std::unique_ptr<const VAO> vao = std::make_unique<const VAO>();
	std::unique_ptr<VBO> vbo = std::make_unique<VBO>();
	std::unique_ptr<const EBO> ebo = nullptr; // EBO need to initialize later

	Vector3f position; // INFO -- 3D default
	Vector2f size;
	float rotate = 0.0f;

	Color color = { 255 };
	Texture* texture = nullptr;

	Shape() = default;
	Shape(const Vector3f position, const Vector2f size, const float rotate);

	inline void colorize(const Color& color) {
		this->color = color;
	}

	inline void bind_texture(Texture* texture) {
		this->texture = texture;
	}

	inline void unbind_texture() {
		this->texture = nullptr;
	}


	virtual inline void set_vbo(const std::vector<float>& vertices) {
		this->vertices = vertices;
		this->vbo->store_two_fields_data(vertices, 3, 2); // INFO -- 3D default
	}

	void set_ebo(const std::vector<unsigned int>& indices);
	void set_vertices(const std::vector<float>& vertices);
	void set_indices(const std::vector<unsigned int>& indices);
	void set_vbo_and_ebo(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
	void set_vertices_and_indices(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
};
