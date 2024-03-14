#pragma once

#include "../../types/texture.hpp"
#include "../../types/color.hpp"
#include "../3d/pyramid.hpp"
#include "../3d/cube.hpp"
#include "renderer.hpp"

class Renderer3D : public Renderer {
	public:
		Renderer3D(const float FOV, const float near_plane, const float far_plane);

		/**
		 * PYRAMID */

		// Texture
		inline void pyramid(const Texture* texture, const float x, const float y, const float z, const float size,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_3d(*this->pyramid_shape, *this->shader_texture, texture, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		}

		// // Texture color first
		// inline void pyramid(const Texture& texture, const float x, const float y, const float z, const float size,
		// 		const Color& color, const float rotate = 0.0f, const bool outline = false) {
		//
		// 	this->draw(ShapeType::PYRAMID, texture, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		// }
		//
		// // Rotate and Outline first
		// inline void pyramid(const float x, const float y, const float z, const float size,
		// 		const float rotate = 0.0f, const bool outline = false, const Color& color = { 0.0f, 0.0f }) {
		//
		// 	this->draw(ShapeType::PYRAMID, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		// }
		//
		// // Color first
		// inline void pyramid(const float x, const float y, const float z, const float size,
		// 	const Color& color, const float rotate = 0.0f, const bool outline = false) {
		//
		// 	this->draw(ShapeType::PYRAMID, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		// }
		//
		// Texture Custom color
		// inline void pyramid(const bool custom_color, const Texture& texture, const float x, const float y, const float z, const float size,
		// 	const Color& color, const float rotate = 0.0f, const bool outline = false) {
		//
		// 	this->draw(ShapeType::PYRAMID, texture, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline, custom_color);
		//
		// 	this->shader->set_int("useCustom", 0);
		// }
		//


		/**
		 * CUBE */
		inline void cube(const Texture* texture, const float x, const float y, const float z, const float width, const float height,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_3d(*this->cube_shape, *this->shader_texture, texture, glm::vec3(x, y, z), glm::vec2(width, height), color, rotate, outline);
		}

		// // Texture color first
		// inline void cube(const Texture& texture, const float x, const float y, const float z, const float width, const float height,
		// 		const Color& color, const float rotate = 0.0f, const bool outline = false) {
		//
		// 	this->draw(ShapeType::CUBE, texture, glm::vec3(x, y, z), glm::vec2(width, height), color, rotate, outline);
		// }
		//
		// // Rotate and Outline first
		// inline void cube(const float x, const float y, const float z, const float width, const float height,
		// 		const float rotate = 0.0f, const bool outline = false, const Color& color = { 0.0f, 0.0f }) {
		//
		// 	this->draw(ShapeType::CUBE, glm::vec3(x, y, z), glm::vec2(width, height), color, rotate, outline);
		// }
		//
		// // Color first
		// inline void cube(const float x, const float y, const float z, const float width, const float height,
		// 	const Color& color, const float rotate = 0.0f, const bool outline = false) {
		//
		// 	this->draw(ShapeType::CUBE, glm::vec3(x, y, z), glm::vec2(width, height), color, rotate, outline);
		// }


		const float fov;
		const float near_plane;
		const float far_plane;

	private:
		// Shapes
		std::unique_ptr<Pyramid> pyramid_shape = std::make_unique<Pyramid>();
		std::unique_ptr<Cube> cube_shape = std::make_unique<Cube>();

		// std::unique_ptr<Pyramid> pyramid_shape = nullptr;
		// std::unique_ptr<Cube> cube_shape = nullptr;

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

