#pragma once

#include "Dynastinae/shapes/3d/pyramid.hpp"
#include "Dynastinae/shapes/3d/cube.hpp"
#include "Dynastinae/types/texture.hpp"
#include "Dynastinae/types/color.hpp"
#include "Dynastinae/scenes/camera.hpp"
#include "Dynastinae/scenes/scene.hpp"
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Scene3D : Scene {
	public:
		Scene3D(Camera& camera);

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

		inline void update_viewport(const Window& window) {
			camera.update_viewport(window.get_width(), window.get_height());
		}

		inline void update_viewport(const uint32 width, const uint32 height) {
			camera.update_viewport(width, height);
		}

	private:
		// Shapes
		Pyramid pyramid_shape = Pyramid();
		Cube cube_shape = Cube();
		Camera& camera;


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
