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


// #define TAU 6.283185307179586


// https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/engine/Camera.java
class Camera : public Renderer {
	public:
		Camera(const Window& window);
		Camera(const unsigned int width, const unsigned int height);

		/**
		 * PYRAMID */

		// Texture
		inline void pyramid(const Texture* texture, const Vector3f position,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_3d(this->pyramid_shape, *this->shader_texture, texture, position, color, rotate, axis.to_glm(), draw_mode);
		}

		// Color first
		inline void pyramid(const Vector3f position,
				const Color& color, const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_3d(this->pyramid_shape, *this->shader, nullptr, position, color, rotate, axis.to_glm(), draw_mode);
		}

		// Rotate and draw_mode first
		inline void pyramid(const Vector3f position,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_3d(this->pyramid_shape, *this->shader, nullptr, position, color, rotate, axis.to_glm(), draw_mode);
		}


		/**
		 * CUBE */
		inline void cube(const Texture* texture, const Vector3f position,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_3d(this->cube_shape, *this->shader_texture, texture, position, color, rotate, axis.to_glm(), draw_mode);
		}

		// Rotate and draw_mode first
		inline void cube(const Vector3f position,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_3d(this->cube_shape, *this->shader, nullptr, position, color, rotate, axis.to_glm(), draw_mode);
		}

		// Color first
		inline void cube(const Vector3f position,
				const Color& color, const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_3d(this->cube_shape, *this->shader, nullptr, position, color, rotate, axis.to_glm(), draw_mode);
		}



		/**
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

		/**
		 * GETTERS */
		inline float get_fov() {
			return this->fov;
		}

		inline float get_near_plane() {
			return this->near_plane;
		}

		inline float get_far_plane() {
			return this->far_plane;
		}

		inline float get_speed() {
			return this->speed;
		}

		inline float get_sensitivity() {
			return this->sensitivity;
		}

		inline Vector2i get_viewport() {
			return { static_cast<int>(this->width), static_cast<int>(this->height) };
		}


		/**
		 * MOVEMENT */
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

		void rotate(Window& window, const Mouse& mouse);


/* TODO -- Test this Rotation

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
		Pyramid pyramid_shape = Pyramid();
		Cube cube_shape = Cube();
		
		// Configuration 
		float fov = 45.0f;
		float near_plane = 0.1f;
		float far_plane = 100.0f;
		float speed = 0.1f;
		float sensitivity = 100.0f;

		// Movement
		bool firstclick = true;
		glm::vec3 position = { 0.0f, 0.0f, 2.0f };
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		// Vector3f rotation = { TAU / 4, 0.0f, 0.0f }; // Just testing


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
			const float rotate = 0.0f, const glm::vec3 axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) const;
};

