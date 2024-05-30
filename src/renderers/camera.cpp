#include "Dynastinae/renderers/camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>

Camera::Camera(const Window& window) : Renderer(window) {
	// Make shaders
	this->shader = new ShaderProgram(this->vertex_shader, this->fragment_shader);
	this->shader_texture = new ShaderProgram(this->vertex_shader_texture, this->fragment_shader_texture);
}

Camera::Camera(const uint32 width, const uint32 height) : Renderer(width, height) {
	// Make shaders
	this->shader = new ShaderProgram(this->vertex_shader, this->fragment_shader);
	this->shader_texture = new ShaderProgram(this->vertex_shader_texture, this->fragment_shader_texture);
}


void Camera::draw_3d(const Shape3D& shape, const ShaderProgram& shader,
	const Texture* texture, const vec3<float>& pos, const Color& color,
	const float rotate, const glm::vec3& axis, const DrawMode draw_mode) const {

	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(draw_mode));

	shader.use();

	glm::mat4 mview = glm::mat4(1.0f); // Model View Matrix
	glm::mat4 proj = glm::mat4(1.0f);


	/* OLD - For reference
	// Rotate on Y-Axis
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(axis.x, axis.y, axis.z));

	// Position
	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	view = glm::translate(view, glm::vec3(pos.x, pos.y, pos.z));

	// Camera
	proj = glm::perspective(glm::radians(this->fov),
			static_cast<float>(Window::static_width()) / static_cast<float>(Window::static_height()),
			this->near_plane, this->far_plane);
	*/




	// float x = this->rotation.x + TAU / 4;
	// mview = glm::rotate(mview, glm::radians(x), glm::vec3(0.0f, 1.0f, 0.0f));
	// mview = glm::rotate(mview, glm::radians(-this->rotation.y), glm::vec3(std::cos(x), 0.0f, std::sin(x)));
	// mview = glm::translate(mview, glm::vec3(-this->position.x, -this->position.y, -this->position.z));

	// Makes camera look in the right direction from the right position
	mview = glm::rotate(mview, glm::radians(rotate), axis);
	mview = glm::lookAt(this->position, (this->position + this->orientation), this->up);

	// Add perspective
	proj = glm::perspective(glm::radians(this->fov),
			(static_cast<float>(this->width) / static_cast<float>(this->height)), this->near_plane, this->far_plane);

	// Apply changes
	shader.set_matrix4f("camMatrix", proj * mview);
	shader.set_vector4f("shapeColor", { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f });

	// If using texture, bind texture
	if(texture != nullptr) {
		texture->bind();
	}

	shape.vao->bind();

	// Triangle just for example
	glDrawElements(GL_TRIANGLES, shape.indices_size, GL_UNSIGNED_INT, (void*)0);

}



void Camera::rotate(Window& window, const Mouse& mouse) {
	if(mouse.down != MouseBTN::LMB) {
		this->firstclick = true;
		return;
	}

	if(this->firstclick) {
		window.set_cursor_position(this->width / 2, this->height / 2);
		this->firstclick = false;
	}

	float rotation_x = this->sensitivity * (static_cast<float>(mouse.axis.y) - static_cast<float>(this->height) / 2) / static_cast<float>(this->height);
	float rotation_y = this->sensitivity * (static_cast<float>(mouse.axis.x) - static_cast<float>(this->width) / 2) / static_cast<float>(this->width);

	// Calcs upcoming vertical change in the orientation
	glm::vec3 new_orientation = glm::rotate(this->orientation, glm::radians(-rotation_x), glm::normalize(glm::cross(this->orientation, this->up)));

	// Check if can move camera
	if(std::abs(glm::angle(new_orientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
		this->orientation = new_orientation;
	}

	// Rotates orientation left and right
	this->orientation = glm::rotate(this->orientation, glm::radians(-rotation_y), this->up);

	// Set cursor to the middle of the screen
	window.set_cursor_position(width / 2, height / 2);
}


