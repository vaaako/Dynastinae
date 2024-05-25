#include "../../../include/shapes/renderer/renderer2d.hpp"
#include "../../../include/window/window.hpp"

Renderer2D::Renderer2D(const Window& window) : Renderer(window) {
	this->update_viewport(window);
}

Renderer2D::Renderer2D(const uint32 width, const uint32 height) : Renderer(width, height) {
	this->update_viewport(width, height);
}


void Renderer2D::update_viewport(const uint32 width, const uint32 height) {
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
}





void Renderer2D::draw_2d(const Shape2D& shape, const ShaderProgram& shader, const GLenum draw_type,
		const Texture* texture, const vec2<float>& pos, const vec2<float>& size, const Color& color,
		const float rotate, const DrawMode draw_mode) const {

	glPolygonMode(GL_FRONT_AND_BACK, static_cast<int>(draw_mode));

	shader.use();

	glm::mat4 model = glm::mat4(1.0f);

	// Move, Resize and rotate
	model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));                   // Translate position
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Origin from top-lef to center
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Origin back to top-left
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));                     // Resize

	// Apply changes
	shader.set_matrix4f("model", model);
	shader.set_vector4f("shapeColor", vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));

	// TODO -- Think on a way of avoiding "if"
	//         + Think on something to add on shader
	if(texture != nullptr) {
		texture->bind();
	}

	shape.vao->bind();
	glDrawElements(draw_type, shape.indices_size, GL_UNSIGNED_INT, (void*)0);
	// glDrawArrays(draw_type, 0, shape.vertices_count);
}


