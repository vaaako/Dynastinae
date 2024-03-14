#pragma once

#include "renderer.hpp"
#include "../../types/texture.hpp"
#include "../../types/color.hpp"
#include "../2d/triangle.hpp"
#include "../2d/rectangle.hpp"


class Renderer2D : public Renderer {
	public:
		Renderer2D();

		// TODO -- Think on a better way of drawing shapes function, because this is getting too much

		/**
		 * TRIANGLE */

		// Texture
		inline void triangle(const Texture* texture, const float x, const float y, const float size, 
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_2d(*this->triangle_shape, *this->shader_texture, GL_TRIANGLES, texture, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}

		// Rotate and Outline first
		inline void triangle(const float x, const float y, const float size, const float rotate = 0.0f,
				const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_2d(*this->triangle_shape, *this->shader, GL_TRIANGLES, nullptr, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}

		// Color first
		inline void triangle(const float x, const float y, const float size,
				const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw_2d(*this->triangle_shape, *this->shader, GL_TRIANGLES, nullptr, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}


		/**
		 * RECTANGLE */

		// Texture
		inline void rectangle(const Texture* texture, const float x, const float y, const float width, const float height,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_2d(*this->rectangle_shape, *this->shader_texture, GL_TRIANGLES, texture, glm::vec2(x, y), glm::vec2(width, height), color, rotate, outline);
		}

		// Rotate and Outline first
		inline void rectangle(const float x, const float y, const float width, const float height,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw_2d(*this->rectangle_shape, *this->shader, GL_TRIANGLES, nullptr, glm::vec2(x, y), glm::vec2(width, height), color, rotate, outline);
		}

		// Color first
		inline void rectangle(const float x, const float y, const float width, const float height,
			const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw_2d(*this->rectangle_shape, *this->shader, GL_TRIANGLES, nullptr, glm::vec2(x, y), glm::vec2(width, height), color, rotate, outline);
		}



	private:
		// Shapes
		std::unique_ptr<Triangle> triangle_shape = std::make_unique<Triangle>();
		std::unique_ptr<Rectangle> rectangle_shape = std::make_unique<Rectangle>();

		// Shaders
		const char* vertex_shader = R"(
			#version 330 core

			layout (location = 0) in vec2 aPos;

			uniform mat4 model;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * model * vec4(aPos.xy, 0.0f, 1.0);
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

			layout (location = 0) in vec2 aPos;
			layout (location = 1) in vec2 aTex;

			out vec2 texCoord;

			uniform mat4 model;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * model * vec4(aPos.xy, 0.0f, 1.0);
				texCoord    = aTex;
			}
		)";

		const char* fragment_shader_texture = R"(
			#version 330 core

			out vec4 FragColor;
			in vec2 texCoord;

			uniform sampler2D texSampler;

			uniform vec4 shapeColor; // Color is defined by user later

			void main() {
				FragColor = texture(texSampler, texCoord) * vec4(shapeColor.rgba);
			}
		)";
};

