#include "../../include/shapes/shape.hpp"
#include <stdexcept>

Shape::Shape(const vec3<float>& position, const vec2<float>& size, const float rotate)
	: position(position), size(size), rotate(rotate) {}

void Shape::set_ebo(const std::vector<uint32>& indices) {
	this->ebo = std::make_unique<const EBO>(indices);
	this->set_indices(indices);
}


void Shape::set_vertices(const std::vector<float>& vertices) {
	if(vertices.empty()) {
		throw std::runtime_error("<vertices.hpp> Can't set vertices because vertices are empty!");
	}

	this->vertices = vertices;
}

void Shape::set_indices(const std::vector<uint32>& indices) {
	if(indices.empty()) {
		throw std::runtime_error("<shape.hpp> Can't set indices because indices are empty!");
	}

	this->indices = indices;
	this->indices_size = static_cast<GLsizei>(indices.size());
}


void Shape::set_vbo_and_ebo(const std::vector<float>& vertices, const std::vector<uint32>& indices) {
	this->vao->bind();

	this->set_vbo(vertices);
	this->set_ebo(indices);

	// Unbind
	this->vao->unbind();
	this->ebo->unbind();
}


void Shape::set_vertices_and_indices(const std::vector<float>& vertices, const std::vector<uint32>& indices) {
	this->set_vertices(vertices);
	this->set_indices(indices);
}
