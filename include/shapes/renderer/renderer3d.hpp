#pragma once

#include "../../types/texture.hpp"
#include "../../types/color.hpp"
#include "../../types/vectors.hpp"
#include "../3d/pyramid.hpp"
#include "../3d/cube.hpp"
#include "renderer.hpp"



// https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/engine/Camera.java
class Renderer3D : public Renderer {
	public:
		Renderer3D(const float FOV, const float near_plane, const float far_plane);

		/**
		 * PYRAMID */

		// Texture
		inline void pyramid(const Texture* texture, const float x, const float y, const float z,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_3d(*this->pyramid_shape, *this->shader_texture, texture, glm::vec3(x, y, z), color, rotate, axis, outline);
		}

		// Rotate and Outline first
		inline void pyramid(const float x, const float y, const float z,
				const Color& color = { 1.0f }, const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false) {

			this->draw_3d(*this->pyramid_shape, *this->shader, nullptr, glm::vec3(x, y, z), color, rotate, axis, outline);
		}

		// Color first
		inline void pyramid(const float x, const float y, const float z,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_3d(*this->pyramid_shape, *this->shader, nullptr, glm::vec3(x, y, z), color, rotate, axis, outline);
		}


		/**
		 * CUBE */
		inline void cube(const Texture* texture, const float x, const float y, const float z,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_3d(*this->cube_shape, *this->shader_texture, texture, glm::vec3(x, y, z), color, rotate, axis, outline);
		}

		// Rotate and Outline first
		inline void cube(const float x, const float y, const float z,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_3d(*this->cube_shape, *this->shader, nullptr, glm::vec3(x, y, z), color, rotate, axis, outline);
		}

		// Color first
		inline void cube(const float x, const float y, const float z,
				const Color& color = { 1.0f }, const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false) {

			this->draw_3d(*this->cube_shape, *this->shader, nullptr, glm::vec3(x, y, z), color, rotate, axis, outline);
		}


		const float fov;
		const float near_plane;
		const float far_plane;

	private:
		// Shapes
		std::unique_ptr<Pyramid> pyramid_shape = std::make_unique<Pyramid>();
		std::unique_ptr<Cube> cube_shape = std::make_unique<Cube>();

		const char* vertex_shader = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 proj;

			void main() {
				gl_Position = proj * view * model * vec4(aPos, 1.0);
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

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 proj;

			void main() {
				gl_Position = proj * view * model * vec4(aPos, 1.0);
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
};

