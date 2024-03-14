#include "../../../include/shapes/renderer/renderer3d.hpp"
#include <memory>

Renderer3D::Renderer3D(const float FOV, const float near_plane, const float far_plane)
	: fov(FOV), near_plane(near_plane), far_plane(far_plane) {

	// Make shaders
	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
	this->shader_texture = std::make_unique<const ShaderProgram>(this->vertex_shader_texture, this->fragment_shader_texture);
}

