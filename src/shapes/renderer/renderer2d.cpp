#include "../../../include/shapes/renderer/renderer2d.hpp"
#include "../../../include/window/window.hpp"

Renderer2D::Renderer2D() {
	// Make camera
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::static_width()), 
		static_cast<float>(Window::static_height()), 0.0f, -1.0f, 1.0f);

	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
	this->shader_texture = std::make_unique<const ShaderProgram>(this->vertex_shader_texture, this->fragment_shader_texture);

	// If don't "set" shader in this order, shaders won't work
	this->shader->use();
	this->shader->set_matrix4f("projection", projection);

	this->shader_texture->use();
	this->shader_texture->set_matrix4f("projection", projection);
}

