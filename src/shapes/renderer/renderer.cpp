#include "../../../include/shapes/renderer/renderer.hpp"
#include "../../../include/window/window.hpp"

/**
 * DRAW 2D
 * */
void Renderer::draw_2d(const Shape2D& shape, const ShaderProgram& shader, const GLenum draw_type,
		const Texture* texture, const Vector2f pos, Vector2f size, const Color& color,
		const float rotate, const DrawMode draw_mode) const {

	glPolygonMode(GL_FRONT_AND_BACK, (int)draw_mode);

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
	shader.set_vector4f("shapeColor", Vector4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));

	// TODO -- Think on a way of avoiding "if"
	//         + Think on something to add on shader
	if(texture != nullptr)
		texture->bind();

	shape.vao->bind();
	glDrawElements(draw_type, shape.indices_size, GL_UNSIGNED_INT, (void*)0);
	// glDrawArrays(draw_type, 0, shape.vertices_count);
}




/**
 * DRAW 3D
 * */
void Renderer::draw_3d(const Shape3D& shape, const ShaderProgram& shader,
		const Texture* texture, const Vector3f pos, const Color& color,
		const float rotate, const Vector3f axis, const DrawMode draw_mode) const {

	glPolygonMode(GL_FRONT_AND_BACK, (int)draw_mode);

	shader.use();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view  = glm::mat4(1.0f);
	glm::mat4 proj  = glm::mat4(1.0f);

	// Rotate on Y-Axis
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(axis.x, axis.y, axis.z));

	// Position
	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	view = glm::translate(view, glm::vec3(pos.x, pos.y, pos.z));

	// Camera
	proj = glm::perspective(glm::radians(this->fov),
			static_cast<float>(Window::static_width()) / static_cast<float>(Window::static_height()),
			this->near_plane, this->far_plane);

	// Apply changes
	shader.set_matrix4f("model", model);
	shader.set_matrix4f("view", view);
	shader.set_matrix4f("proj", proj);

	shader.set_vector4f("shapeColor", Vector4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));

	// TODO -- Think on a way of avoiding "if"
	//         + Think on something to add on shader
	if(texture != nullptr)
		texture->bind();

	shape.vao->bind();
	glDrawElements(GL_TRIANGLES, shape.indices_size, GL_UNSIGNED_INT, (void*)0);
}
