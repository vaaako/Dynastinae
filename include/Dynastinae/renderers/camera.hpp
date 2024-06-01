#pragma once

#include "Dynastinae/shapes/3d/pyramid.hpp"
#include "Dynastinae/shapes/3d/cube.hpp"
#include "Dynastinae/types/texture.hpp"
#include "Dynastinae/types/color.hpp"
#include "Dynastinae/renderers/renderer.hpp"
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Camera : public Renderer {
	public:
		Camera(const Window& window, const float fov = 45.0f, const float sensitivity = 100.0f);
		Camera(const uint32 width, const uint32 height, const float fov = 45.0f, const float sensitivity = 100.0f);

		/**
		 * PYRAMID */

		// Texture
		inline void pyramid(const Texture* texture, const vec3<float>& position,
				const float rotate = 0.0f, const vec3<float>& axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_3d(this->pyramid_shape, *this->shader_texture, texture, position.to_glm(), color, rotate, axis.to_glm(), draw_mode);
		}

		// Color first
		inline void pyramid(const vec3<float>& position,
				const Color& color, const float rotate = 0.0f, const vec3<float>& axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_3d(this->pyramid_shape, *this->shader, nullptr, position.to_glm(), color, rotate, axis.to_glm(), draw_mode);
		}

		// Rotate and draw_mode first
		inline void pyramid(const vec3<float>& position,
				const float rotate = 0.0f, const vec3<float>& axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_3d(this->pyramid_shape, *this->shader, nullptr, position.to_glm(), color, rotate, axis.to_glm(), draw_mode);
		}


		/**
		 * CUBE */
		inline void cube(const Texture* texture, const vec3<float>& position,
				const float rotate = 0.0f, const vec3<float>& axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_3d(this->cube_shape, *this->shader_texture, texture, position.to_glm(), color, rotate, axis.to_glm(), draw_mode);
		}

		// Rotate and draw_mode first
		inline void cube(const vec3<float>& position,
				const float rotate = 0.0f, const vec3<float>& axis = { 0.0f, 0.0f, 0.0f }, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_3d(this->cube_shape, *this->shader, nullptr, position.to_glm(), color, rotate, axis.to_glm(), draw_mode);
		}

		// Color first
		inline void cube(const vec3<float>& position,
				const Color& color, const float rotate = 0.0f, const vec3<float>& axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_3d(this->cube_shape, *this->shader, nullptr, position.to_glm(), color, rotate, axis.to_glm(), draw_mode);
		}



		/**
		 * SETTERS */
		inline void set_fov(const float fov) {
			this->fov = fov;
		}

		// Set the minimum amount of fov possible (used in zoom out)
		inline void set_min_fov(const float min_fov) {
			this->min_fov = min_fov;
		}

		// Set the maximum amount of fov possible (used in zoom out)
		inline void set_max_fov(const float max_fov) {
			this->max_fov = max_fov;
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

		// TODO -- not sure if i have to change glViewPort too
		inline void update_viewport(const Window& window) {
			this->update_viewport(window.get_width(), window.get_height());
		}

		inline void update_viewport(const uint32 width, const uint32 height) {
			this->width = width;
			this->height = height;
		}

		/**
		 * GETTERS */
		inline float get_fov() const {
			return this->fov;
		}

		inline float get_near_plane() const {
			return this->near_plane;
		}

		inline float get_far_plane() const {
			return this->far_plane;
		}

		inline float get_speed() const {
			return this->speed;
		}

		inline float get_sensitivity() const {
			return this->sensitivity;
		}

		inline vec2<int> get_viewport() const {
			return { static_cast<int>(this->width), static_cast<int>(this->height) };
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

		/*
		 * Zoom in, in a certain speed, to instant zoom in, set the speed to equal or higher than the current fov
		 *
		 * You can change "min_fov" to set the zoom in distance
		 */
		void zoom_in(const float speed);

		/* Zoom out, in a certain speed, to instant zoom out, set the speed to equal or higher than the current fov
		 *
		 * You can change "max_fov" to set the zoom out distance
		 */
		void zoom_out(const float speed);

		void rotate(const Mouse& mouse);


		// TEST //
		inline void can_move(const bool can_move) {
			this->firstclick = can_move;
		}
		// TEST //
	private:
		// Shapes
		Pyramid pyramid_shape = Pyramid();
		Cube cube_shape = Cube();
		
		// Configuration 
		float fov;
		float min_fov = 20.0f;
		float max_fov = 100.0f;
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



		const char* vertex_shader = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			uniform mat4 mvp;

			void main() {
				gl_Position = mvp * vec4(aPos, 1.0);
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
			// layout (location = 2) in float aSha; // Shader (shadow)

			out vec2 texCoord;
			uniform mat4 mvp;

			void main() {
				gl_Position = mvp * vec4(aPos, 1.0);
				texCoord    = aTex;
				// shadingValue = aSha;
			}
		)";

		const char* fragment_shader_texture = R"(
			#version 330 core

			in vec2 texCoord;
			out vec4 FragColor;

			uniform sampler2D texSampler;
			uniform vec4 shapeColor; // Color is defined by user later

			void main() {
				vec4 texColor = texture(texSampler, texCoord) * vec4(shapeColor.rgba);
				FragColor = texColor;

				// FragColor = texColor * shadingValue // Shadow
			}
		)";


		inline void init_shaders() {
			// Make shaders
			this->shader = new ShaderProgram(this->vertex_shader, this->fragment_shader);
			this->shader_texture = new ShaderProgram(this->vertex_shader_texture, this->fragment_shader_texture);
		}

		void draw_3d(const Shape3D& shape, const ShaderProgram& shader,
			const Texture* texture, const glm::vec3& pos, const Color& color = { 255 },
			const float rotate = 0.0f, const glm::vec3& axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) const;
};

