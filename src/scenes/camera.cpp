#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>

#include "Dynastinae/scenes/camera.hpp"

Camera::Camera(const Window& window, const float fov, const float sensitivity)
	: fov(fov), sensitivity(sensitivity), width(window.get_width()), height(window.get_height()), max_fov(fov) {}

Camera::Camera(const uint32 width, const uint32 height, const float fov, const float sensitivity)
	: fov(fov), sensitivity(sensitivity), width(width), height(height), max_fov(fov) {}


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

