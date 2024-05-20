#pragma once

#include "../../types/texture.hpp"
#include "../../types/color.hpp"
#include "../../types/vectors.hpp"
#include "../3d/pyramid.hpp"
#include "../3d/cube.hpp"
#include "renderer.hpp"


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


#define TAU 6.283185307179586


// https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/engine/Camera.java
class Camera : public Renderer {
	public:
		Camera(const Window& window);
		Camera(const unsigned int width, const unsigned int height);


		/**
		 * PYRAMID */

		// Texture
		inline void pyramid(const Texture* texture, const float x, const float y, const float z,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			// this->draw_3d(*this->pyramid_shape, *this->shader_texture, texture, Vector3f(x, y, z), color, rotate, axis, draw_mode);
			this->matrix(*this->pyramid_shape, *this->shader_texture, texture, color, rotate, axis, draw_mode);
		}

		// NOTE -- Commenting so i can test matrix and implement after
		// Color first
		// inline void pyramid(const float x, const float y, const float z,
		// 		const Color& color, const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) {
		//
		// 	this->draw_3d(*this->pyramid_shape, *this->shader, nullptr, Vector3f(x, y, z), color, rotate, axis, draw_mode);
		// }
		//
		// // Rotate and draw_mode first
		// inline void pyramid(const float x, const float y, const float z,
		// 		const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {
		//
		// 	this->draw_3d(*this->pyramid_shape, *this->shader, nullptr, Vector3f(x, y, z), color, rotate, axis, draw_mode);
		// }


		/**
		 * CUBE */
		// inline void cube(const Texture* texture, const float x, const float y, const float z,
		// 		const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {
		//
		// 	this->draw_3d(*this->cube_shape, *this->shader_texture, texture, Vector3f(x, y, z), color, rotate, axis, draw_mode);
		// }
		//
		// // Rotate and draw_mode first
		// inline void cube(const float x, const float y, const float z,
		// 		const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {
		//
		// 	this->draw_3d(*this->cube_shape, *this->shader, nullptr, Vector3f(x, y, z), color, rotate, axis, draw_mode);
		// }
		//
		// // Color first
		// inline void cube(const float x, const float y, const float z,
		// 		const Color& color, const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) {
		//
		// 	this->draw_3d(*this->cube_shape, *this->shader, nullptr, Vector3f(x, y, z), color, rotate, axis, draw_mode);
		// }



		/*
		* SETTERS */
		inline void set_fov(const float fov) {
			this->fov = fov;
		}

		inline void set_near_plane(const float near_plane) {
			this->near_plane = near_plane;
		}

		inline void set_far_plane(const float far_plane) {
			this->far_plane = far_plane;
		}

		inline void set_speed(const float speed) {
			this->speed = speed;
		}

		inline void set_sensitivity(const float sensitivity) {
			this->sensitivity = sensitivity;
		}

		inline void update_viewport(const Window& window) {
			this->width = window.get_width();
			this->height = window.get_height();
		}

		inline void update_viewport(const unsigned int width, const unsigned int height) {
			this->width = width;
			this->height = height;
		}


		// TESTING ONLY //
		inline void go_foward() {
			this->position += this->speed * this->orientation;
		}

		inline void go_back() {
			this->position += this->speed * -this->orientation;
		}

		inline void go_left() {
			this->position += this->speed * -glm::normalize(glm::cross(this->orientation, this->up));
		}

		inline void go_right() {
			this->position += this->speed * glm::normalize(glm::cross(this->orientation, this->up));
		}


		// Fly
		inline void go_up() {
			this->position += this->speed * this->up;
		}

		inline void go_down() {
			this->position += this->speed * -this->up;
		}


		inline void rotate(Window& window, const Mouse& mouse) {
			if(mouse.down != MouseBTN::LMB) {
				this->firstclick = false;
				return;
			}

			if(this->firstclick) {
				window.set_cursor_position(this->width / 2, this->height / 2);
				this->firstclick = false;
			}

			// get cursor position for this calc
			
			float rotation_x = this->sensitivity * ((float)mouse.axis.y - ((float)this->height / 2)) / this->height;
			float rotation_y = this->sensitivity * ((float)mouse.axis.x - ((float)this->width / 2)) / this->width;

			// Calcs upcoming vertical change in the orientation
			glm::vec3 new_orientation = glm::rotate(this->orientation, glm::radians(-rotation_x),
													glm::normalize(glm::cross(this->orientation, this->up)));

			// Check if can move camera
			if(std::abs(glm::angle(new_orientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				this->orientation = new_orientation;
			}

			// Rotates orientation left and right
			this->orientation = glm::rotate(this->orientation, glm::radians(-rotation_y), this->up);

			// Set cursor to the middle of the screen
			window.set_cursor_position(width / 2, height / 2);
		}


		bool firstclick = true;
		// TESTING ONLY //
 
		float fov = 45.0f;
		float near_plane = 0.1f;
		float far_plane = 100.0f;

		glm::vec3 position = { 0.0f, 0.0f, 2.0f };
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		// Vector3f rotation = { TAU / 4, 0.0f, 0.0f }; // Just testing

		float speed = 0.1f;
		float sensitivity = 100.0f;


/* TODO -- Rotation

 	private Vector3f rotation = new Vector3f((float) Math.TAU / 4, 0.0f, 0.0f);
	public void moveRotation(double xpos, double ypos) {
		// rotation.x -= xpos * sensitivity;
		rotation.x += xpos * sensitivity;
		rotation.y += ypos * sensitivity;
		// rotation.z += offsetZ;

		// Avoid 360º spin (Y only duurh)
		rotation.y = Math.max((float) (-Math.TAU / 4),
			Math.min((float) (Math.TAU / 4), rotation.y)
		);
	}

	public void movePosition(float offsetX, float offsetY, float offsetZ, float speed) {
		float angle = (float)(rotation.x - Math.atan2(offsetZ, offsetX) + (Math.TAU / 4));
		if(offsetX != 0.0f || offsetZ != 0.0f) {
			position.x += (float) Math.cos(angle) * speed * 0.1f;
			position.z += (float) Math.sin(angle) * speed * 0.1f;
		}

		position.y += offsetY * 0.1f;
	}
*/
	private:
		// Shapes
		std::unique_ptr<Pyramid> pyramid_shape = std::make_unique<Pyramid>();
		std::unique_ptr<Cube> cube_shape = std::make_unique<Cube>();

		const char* vertex_shader = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;

			// uniform mat4 model;
			// uniform mat4 view;
			// uniform mat4 proj;

			uniform mat4 camMatrix;

			void main() {
				// gl_Position = proj * view * model * vec4(aPos, 1.0);
				gl_Position = camMatrix * vec4(aPos, 1.0);
			}
		)";

		const char* fragment_shader = R"(
			#version 330 core

			out vec4 FragColor;
			uniform vec4 shapeColor; // Color is defined by user later

			void main() {
				FragColor = vec4(shapeColor.rgba);
			}
		)";


		const char* vertex_shader_texture = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTex;

			out vec2 texCoord;

			// uniform mat4 model;
			// uniform mat4 view;
			// uniform mat4 proj;

			uniform mat4 camMatrix;

			void main() {
				// gl_Position = proj * view * model * vec4(aPos, 1.0);
				gl_Position = camMatrix * vec4(aPos, 1.0);
				texCoord    = aTex;
			}
		)";

		const char* fragment_shader_texture = R"(
			#version 330 core

			in vec2 texCoord;
			out vec4 FragColor;

			uniform sampler2D texSampler;
			uniform vec4 shapeColor; // Color is defined by user later

			void main() {
				FragColor = texture(texSampler, texCoord) * vec4(shapeColor.rgba);
			}
		)";



		void draw_3d(const Shape3D& shape, const ShaderProgram& shader,
			const Texture* texture, Vector3f pos, const Color& color = { 255 },
			const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) const;


		void matrix(const Shape3D& shape, const ShaderProgram& shader,
				const Texture* texture, const Color& color,
				const float rotate, const Vector3f axis, const DrawMode draw_mode);
};

