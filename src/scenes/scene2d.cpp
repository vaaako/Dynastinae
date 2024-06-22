#include "Dynastinae/scenes/scene2d.hpp"
#include "Dynastinae/window/window.hpp"

Scene2D::Scene2D(const Window& window) : Scene(window) {
	this->update_viewport(window.get_width(), window.get_height());
}

Scene2D::Scene2D(const uint32 width, const uint32 height) : Scene(width, height) {
	this->update_viewport(width, height);
}

void Scene2D::update_viewport(const uint32 width, const uint32 height) {
	this->width = width;
	this->height = height;

	// Make camera
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

	this->shader = new ShaderProgram(this->vertex_shader, this->fragment_shader);
	this->shader_texture = new ShaderProgram(this->vertex_shader_texture, this->fragment_shader_texture);

	// If don't "set" shader in this order, shaders won't work
	this->shader->use();
	this->shader->set_matrix4f("projection", projection);

	this->shader_texture->use();
	this->shader_texture->set_matrix4f("projection", projection);

	// Unecessary shader string
	delete []this->vertex_shader;
	delete []this->fragment_shader;
	delete []this->vertex_shader_texture;
	delete []this->fragment_shader_texture;
}

