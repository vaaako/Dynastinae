#pragma once

#include "../renderer.hpp"
#include "../../types/texture.hpp"
#include "../../types/color.hpp"


class Renderer2D : public Renderer {
	public:
		Renderer2D();

		// TODO -- Think on a better way of drawing shapes function, because this is getting too much

		/**
		 * TRIANGLE */

		// Texture
		inline void triangle(const Texture& texture, const float x, const float y, const float size, 
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw(ShapeType::TRIANGLE, texture, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}

		// Texture color first
		inline void triangle(const Texture& texture, const float x, const float y, const float size,
			const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw(ShapeType::TRIANGLE, texture, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}

		// Rotate and Outline first
		inline void triangle(const float x, const float y, const float size, const float rotate = 0.0f,
				const bool outline = false, const Color& color = { 0.0f, 0.0f }) {

			this->draw(ShapeType::TRIANGLE, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}

		// Color first
		inline void triangle(const float x, const float y, const float size,
				const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw(ShapeType::TRIANGLE, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline);
		}

		// Custom color
		inline void triangle(const bool custom_color, const float x, const float y, const float size,
			const float rotate = 0.0f, const bool outline = false, const Color& color = Color { 0.0f, 0.0f }) {

			this->draw(ShapeType::TRIANGLE, glm::vec2(x, y), glm::vec2(size, size), color, rotate, outline, custom_color);

			// Unuse for other shapes
			this->shader->set_int("useCustom", 0);
		}




		/**
		 * RECTANGLE */

		// Texture
		inline void rectangle(const Texture& texture, const float x, const float y, const float width, const float height,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw(ShapeType::RECTANGLE, texture, glm::vec2(x, y), glm::vec2(width, height),
					color, rotate, outline);
		}

		// Texutre color first
		inline void rectangle(const Texture& texture, const float x, const float y, const float width, const float height,
			const Color& color = { 1.0f }, const float rotate = 0.0f, const bool outline = false) {

			this->draw(ShapeType::RECTANGLE, texture, glm::vec2(x, y), glm::vec2(width, height),
					color, rotate, outline);
		}

		// Rotate and Outline first
		inline void rectangle(const float x, const float y, const float width, const float height,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 0.0f, 0.0f }) {

			this->draw(ShapeType::RECTANGLE, glm::vec2(x, y), glm::vec2(width, height), color, rotate, outline);
		}

		// Color first
		inline void rectangle(const float x, const float y, const float width, const float height,
			const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw(ShapeType::RECTANGLE, glm::vec2(x, y), glm::vec2(width, height), color, rotate, outline);
		}

		// Custom color
		inline void rectangle(const bool custom_color, const float x, const float y, const float width, const float height,
			const float rotate = 0.0f, const bool outline = false, const Color& color = Color { 0.0f, 0.0f }) {

			this->draw(ShapeType::RECTANGLE, glm::vec2(x, y), glm::vec2(width, height), color, rotate, outline, custom_color);

			// Unuse for other shapes
			this->shader->set_int("useCustom", 0);
		}


	private:
		enum class ShapeType {
			TRIANGLE,
			RECTANGLE
		};

		const char* vertex_shader = R"(
			#version 330 core

			layout (location = 0) in vec2 aPos;
			layout (location = 2) in vec4 aColor;

			uniform mat4 model;
			uniform mat4 projection;

			out vec4 customColor;

			void main() {
				gl_Position = projection * model * vec4(aPos.xy, 0.0f, 1.0);
				customColor = aColor;
			}
		)";

		const char* fragment_shader = R"(
			#version 330 core

			in vec4 customColor;
			out vec4 FragColor;

			uniform vec4 shapeColor; // Color is defined by user later
			uniform int useCustom = 0;

			void main() {
				if(useCustom == 1) {
					FragColor = vec4(customColor.rgba);
				} else {
					FragColor = vec4(shapeColor.rgba);
				}
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



		inline void draw(const ShapeType shape, const Texture& texture,
				const glm::vec2 pos, glm::vec2 size, const Color& color,
				const float rotate, const bool outline, const bool custom_color = false) {

			this->draw_2d(texture, pos, size, color, rotate, outline, custom_color);


			// Draw shape
			this->vao->bind();
			if(shape == ShapeType::TRIANGLE) {
				glDrawArrays(GL_TRIANGLES, 0, 3);
			} else {
				glDrawArrays(GL_QUADS, 3, 4);
			}
			this->vao->unbind();
		}

		inline void draw(const ShapeType shape, const glm::vec2 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {

			this->draw_2d(pos, size, color, rotate, outline, custom_color);

			// Draw shape
			this->vao->bind();
			if(shape == ShapeType::TRIANGLE) {
				glDrawArrays(GL_TRIANGLES, 0, 3);
			} else {
				glDrawArrays(GL_QUADS, 3, 4);
			}
			this->vao->unbind();
		}
};

