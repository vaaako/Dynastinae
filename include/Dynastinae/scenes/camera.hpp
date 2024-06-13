#pragma once

#include "Dynastinae/types.hpp"
#include "Dynastinae/window/window.hpp"
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Camera {
	// Mesh and Childs
	friend struct Mesh; // Mesh can acess private members of Camera (for movement)

	public:
		float sensitivity;
		float speed = 0.1f;

		Camera(const Window& window, const float fov = 45.0f, const float sensitivity = 100.0f);
		Camera(const uint32 width, const uint32 height, const float fov = 45.0f, const float sensitivity = 100.0f);

		/**
		 * GETTERS */
		inline uint32 get_width() const {
			return this->width;
		}

		inline uint32 get_height() const {
			return this->height;
		}

		inline vec2<uint32> get_viewport() const {
			return { this->width, this->height };
		}

		/**
		 * SETTERS */
		void set_near_plane(const float near_plane);
		void set_far_plane(const float far_plane);
		void set_fov(const float fov);

		// Set the minimum amount of fov possible (used for zoom out)
		void set_min_fov(const float min_fov);

		// Set the maximum amount of fov possible (used for zoom out)
		void set_max_fov(const float max_fov);

		inline void update_viewport(const uint32 width, const uint32 height) {
			this->width = width;
			this->height = height;
		}



		/**
		 * MOVEMENT */
		inline void move_foward() {
			this->position += this->orientation * this->speed;
		}

		inline void move_backward() {
			this->position -= this->orientation * this->speed;
		}

		inline void move_left() {
			this->position -= glm::normalize(glm::cross(this->orientation, this->up)) * this->speed;
		}

		inline void move_right() {
			this->position += glm::normalize(glm::cross(this->orientation, this->up)) * this->speed ;
		}

		// Fly

		// Go up
		inline void move_up() {
			this->position += this->up * this->speed;
		}

		// Go up
		inline void move_down() {
			this->position -= this->up * this->speed;
		}

		// Zoom in, in a certain speed, to instant zoom in, set the speed to equal or higher than the current fov
		//
		// You can change "min_fov" to set the zoom in distance
		void zoom_in(const float speed);

		// Zoom out, in a certain speed, to instant zoom out, set the speed to equal or higher than the current fov
		//
		// You can change "max_fov" to set the zoom out distance
		void zoom_out(const float speed);

		void rotate(const Mouse& mouse);

	private:
		// Configuration 
		uint32 width;
		uint32 height;

		float fov;
		float max_fov;
		float min_fov = 10.0f;
		float near_plane = 0.1f;
		float far_plane = 100.0f;

		// Movement
		bool firstclick = true;
		// -90 in yaw prevents camera from jumping on the first click
		float yaw = -90.0f; // Horizontal rotation
		float pitch = 0.0f; // Vertical rotation

		glm::vec3 position = { 0.0f, 0.0f, 2.0f };
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

