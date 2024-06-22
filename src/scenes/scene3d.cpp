#include "Dynastinae/scenes/scene3d.hpp"


Scene3D::Scene3D(Camera& camera)
	: Scene(camera.get_width(), camera.get_height()), camera(camera) {

	this->shader = new ShaderProgram(this->vertex_shader, this->fragment_shader);
	this->shader_texture = new ShaderProgram(this->vertex_shader_texture, this->fragment_shader_texture);

	// Unecessary shader string
	delete []this->vertex_shader;
	delete []this->fragment_shader;
	delete []this->vertex_shader_texture;
	delete []this->fragment_shader_texture;
}

