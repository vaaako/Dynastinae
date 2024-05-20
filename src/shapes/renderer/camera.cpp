#include "../../../include/shapes/renderer/camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>

Camera::Camera(const Window& window) : Renderer(window) {
	// Make shaders
	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
	this->shader_texture = std::make_unique<const ShaderProgram>(this->vertex_shader_texture, this->fragment_shader_texture);
}

Camera::Camera(const unsigned int width, const unsigned int height) : Renderer(width, height) {
	// Make shaders
	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
	this->shader_texture = std::make_unique<const ShaderProgram>(this->vertex_shader_texture, this->fragment_shader_texture);
}


void Camera::draw_3d(const Shape3D& shape, const ShaderProgram& shader,
		const Texture* texture, Vector3f pos, const Color& color,
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
			((float)this->width / (float)this->height),
			this->near_plane, this->far_plane);

	// Apply changes
	shader.set_matrix4f("camMatrix", proj * view);
	shader.set_vector4f("shapeColor", Vector4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));

	// TODO -- Think on a way of avoiding "if"
	//         + Think on something to add on shader
	if(texture != nullptr)
		texture->bind();

	shape.vao->bind();
	glDrawElements(GL_TRIANGLES, shape.indices_size, GL_UNSIGNED_INT, (void*)0);

}


void Camera::matrix(const Shape3D& shape, const ShaderProgram& shader,
		const Texture* texture, const Color& color,
		const float rotate, const Vector3f axis, const DrawMode draw_mode) {

	glPolygonMode(GL_FRONT_AND_BACK, (int)draw_mode);

	shader.use();

	glm::mat4 mview = glm::mat4(1.0f); // Model View Matrix
	glm::mat4 proj = glm::mat4(1.0f);



	// float x = this->rotation.x + TAU / 4;
	// mview = glm::rotate(mview, glm::radians(x), glm::vec3(0.0f, 1.0f, 0.0f));
	// mview = glm::rotate(mview, glm::radians(-this->rotation.y), glm::vec3(std::cos(x), 0.0f, std::sin(x)));
	// mview = glm::translate(mview, glm::vec3(-this->position.x, -this->position.y, -this->position.z));

	// Makes camera look in the right direction from the right position
	mview = glm::rotate(mview, glm::radians(rotate), glm::vec3(axis.x, axis.y, axis.z));
	mview = glm::lookAt(this->position,
					(this->position + this->orientation), this->up);

	// Add perspective	
	proj = glm::perspective(glm::radians(this->fov),
			((float)this->width / (float)this->height), this->near_plane, this->far_plane);

	// Apply changes
	shader.set_matrix4f("camMatrix", proj * mview);
	shader.set_vector4f("shapeColor", Vector4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));

	// TODO -- Think on a way of avoiding "if"
	//         + Think on something to add on shader
	if(texture != nullptr)
		texture->bind();

	shape.vao->bind();

	// Triangle just for example
	glDrawElements(GL_TRIANGLES, shape.indices_size, GL_UNSIGNED_INT, (void*)0);

}


