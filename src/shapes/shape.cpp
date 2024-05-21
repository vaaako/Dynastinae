#include "../../include/shapes/shape.hpp"
#include <stdexcept>

Shape::Shape(const Vector3f position, const Vector2f size, const float rotate)
	: position(position), size(size), rotate(rotate) {}

void Shape::set_ebo(const std::vector<unsigned int>& indices) {
	this->ebo = std::make_unique<const EBO>(indices);
	this->set_indices(indices);
}


void Shape::set_vertices(const std::vector<float>& vertices) {
	if(vertices.empty()) {
		throw std::runtime_error("<vertices.hpp> Can't set vertices because vertices is empty!");
	}

	this->vertices = vertices;
}

void Shape::set_indices(const std::vector<unsigned int>& indices) {
	if(indices.empty()) {
		throw std::runtime_error("<shape.hpp> Can't set indices because indices is empty!");
	}

	this->indices = indices;
	this->indices_size = static_cast<GLsizei>(indices.size());
}


void Shape::set_vbo_and_ebo(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
	this->vao->bind();

	this->set_vbo(vertices);
	this->set_ebo(indices);

	// Unbind
	this->vao->unbind();
	this->ebo->unbind();
}


void Shape::set_vertices_and_indices(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
	this->set_vertices(vertices);
	this->set_indices(indices);
}
