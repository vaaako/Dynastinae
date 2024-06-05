#pragma once

#include "Dynastinae/types.hpp"
#include "Dynastinae/window/window.hpp"
#include "Dynastinae/utils/log.hpp"
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Camera {
	public:
		float fov;
		float sensitivity;
		float near_plane = 0.1f;
		float far_plane = 100.0f;
		float speed = 0.1f;

		// Movement
		bool firstclick = true;

		// -90 in yaw prevents camera from jumping on the first click
		float yaw = -90.0f; // Horizontal rotation
		float pitch = 0.0f; // Vertical rotation

		glm::vec3 position = { 0.0f, 0.0f, 2.0f };
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);


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
		inline void set_fov(const float fov) {
			this->fov = fov;
		}

		// Set the minimum amount of fov possible (used for zoom out)
		inline void set_min_fov(const float min_fov) {
			if(min_fov < this->max_fov) {
				LOG_ERROR("[set_min_fov] min fov can't be higher than max pov value");
				return;
			}

			this->min_fov = min_fov;
		}

		// Set the maximum amount of fov possible (used for zoom out)
		inline void set_max_fov(const float max_fov) {
			if(max_fov < this->min_fov) {
				LOG_ERROR("max fov can't be lower than min pov value");
				return;
			}

			this->max_fov = max_fov;
		}

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

		float max_fov;
		float min_fov = 10.0f;
};

