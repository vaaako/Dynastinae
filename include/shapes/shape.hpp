#pragma once

#include "../opengl/vbo.hpp"
#include "../opengl/vao.hpp"
#include "../opengl/ebo.hpp"
#include "../types/color.hpp"
#include "../types/texture.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include <glm/fwd.hpp>
#include <memory>
#include <stdexcept>

struct Shape {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	GLsizei indices_size = 0;

	std::unique_ptr<const VAO> vao = std::make_unique<const VAO>();
	std::unique_ptr<VBO> vbo = std::make_unique<VBO>();
	std::unique_ptr<const EBO> ebo = nullptr; // EBO need to initialize later

	glm::vec3 position; // INFO -- 3D default
	glm::vec2 size;
	float rotate = 0.0f;

	Color color = { 1.0f };
	Texture* texture = nullptr;

	Shape() = default;
	Shape(const glm::vec3 position, const glm::vec2 size, const float rotate);

	inline void colorize(const Color& color) {
		this->color.swap_colors(color);
	}

	inline void colorize(const float r, const float g, const float b, const float a = 1.0f) {
		this->color.swap_colors(r, g, b, a);
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

	inline void set_ebo(const std::vector<unsigned int>& indices) {
		this->ebo = std::make_unique<const EBO>(indices);
		this->set_indices(indices);
	}


	inline void set_vertices(const std::vector<float>& vertices) {
		if(vertices.empty()) {
			throw std::runtime_error("<vertices.hpp> Can't set vertices because vertices is empty!");
		}

		this->vertices = vertices;
	}

	inline void set_indices(const std::vector<unsigned int>& indices) {
		if(indices.empty()) {
			throw std::runtime_error("<shape.hpp> Can't set indices because indices is empty!");
		}

		this->indices = indices;
		this->indices_size = static_cast<GLsizei>(indices.size());
	}


	inline void set_vbo_and_ebo(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
		this->vao->bind();

		this->set_vbo(vertices);
		this->set_ebo(indices);

		// Unbind
		this->vao->unbind();
		this->ebo->unbind();
	}


	inline void set_vertices_and_indices(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
		this->set_vertices(vertices);
		this->set_indices(indices);
	}
};
