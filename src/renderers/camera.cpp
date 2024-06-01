#include "Dynastinae/renderers/camera.hpp"
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(const Window& window, const float fov, const float sensitivity) : Renderer(window), fov(fov), sensitivity(sensitivity) {
	this->init_shaders();
}

Camera::Camera(const uint32 width, const uint32 height, const float fov, const float sensitivity) : Renderer(width, height), fov(fov), sensitivity(sensitivity) {
	this->init_shaders();

}

void Camera::rotate(const Mouse& mouse) {
	// Calculate move relative to the screen middle
	float xoffset = this->sensitivity * (static_cast<float>(mouse.motion.x) - static_cast<float>(this->width) / 2) / static_cast<float>(this->width);
	float yoffset = this->sensitivity * (static_cast<float>(mouse.motion.y) - static_cast<float>(this->height) / 2) / static_cast<float>(this->height);

	this->yaw += xoffset;
	this->pitch -= yoffset;

	// Constrain the pitch
	if(this->pitch > 89.0f) {
		this->pitch = 89.0f;
	} else if(this->pitch < -89.0f) {
		this->pitch = -89.0f;
	}

	// Update orientation
	glm::vec3 front;
	front.x = std::cos(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
	front.y = std::sin(glm::radians(this->pitch));
	front.z = std::sin(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
	this->orientation = glm::normalize(front);
}

void Camera::zoom_in(const float speed) {
	this->fov -= speed;
	if(fov < this->min_fov) {
		this->fov = this->min_fov; // Set a minimum FOV to prevent zooming in too much
	}
}

void Camera::zoom_out(const float speed) {
	this->fov += speed;
	if(this->fov > this->max_fov) {
		fov = this->max_fov; // Set a maximum FOV to prevent zooming out too much
	}
}


void Camera::draw_3d(const Shape3D& shape, const ShaderProgram& shader,
	const Texture* texture, const glm::vec3& pos, const Color& color,
	const float rotate, const glm::vec3& axis, const DrawMode draw_mode) const {

	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(draw_mode));

	// Use shader
	shader.use();

	// Init matrices
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	// Model matrix //
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(rotate), axis);

	// View matrix //
	view = glm::lookAt(this->position, (this->position + this->orientation), this->up);

	// Projection matrix //
	proj = glm::perspective(glm::radians(this->fov), static_cast<float>(this->width) / static_cast<float>(this->height), this->near_plane, this->far_plane);

	// Add perspective
	proj = glm::perspective(glm::radians(this->fov),
			(static_cast<float>(this->width) / static_cast<float>(this->height)), this->near_plane, this->far_plane);

	// Apply changes
	shader.set_matrix4f("mvp", proj * view * model);
	shader.set_vector4f("shapeColor", { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f });

	// If using texture, bind texture
	if(texture != nullptr) {
		texture->bind();
	}

	// bind and draw
	shape.vao->bind();
	glDrawElements(GL_TRIANGLES, shape.indices_size, GL_UNSIGNED_INT, (void*)0);

}

