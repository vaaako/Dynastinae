#pragma once

#include "../renderer.hpp"
#include "../../types/texture.hpp"
#include "../../types/color.hpp"


class Renderer2D : public Renderer {
	public:
		Renderer2D();

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

	private:
		enum class ShapeType {
			TRIANGLE,
			RECTANGLE
		};

		const char* vertex_shader = R"(
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

		const char* fragment_shader = R"(
			#version 330 core

			out vec4 FragColor;
			in vec2 texCoord;
			in vec3 FragPos;

			uniform int useTex = 0;
			uniform sampler2D texSampler;

			uniform vec4 shapeColor; // Color is defined by user later
			uniform mat4 colorMatrix;

			void main() {
				// FragColor = colorMatrix * vec4(texCoord, 0.0, 1.0);
				// FragColor = vec4(colorMatrix[0]);
				// FragColor = colorMatrix[gl_VertexID];

				// FragColor = FragColor * colorMatrix;

				if(useTex == 1) {
					FragColor = texture(texSampler, texCoord) * vec4(shapeColor.rgba);
				} else {
					FragColor = vec4(shapeColor.rgba);
				}
			}
		)";


		/*
		2. Multiple Fragment Shaders:

		- Create separate fragment shaders for textured and untextured shapes.
		- Each shader would only include the relevant texture-related code, avoiding redundant computations.
		- In your drawing loop, bind the appropriate fragment shader based on the shape's texture usage before drawing.
		- This approach requires managing multiple shaders but can potentially improve performance and simplify the code within each shader.
		
		NOTE -- tried but didn't work
		*/


		inline void draw(const ShapeType shape, const Texture& texture,
				const glm::vec2 pos, glm::vec2 size, const Color& color, const float rotate, const bool outline) {
			this->draw_2d(pos, size, color, rotate, outline);
			
			// Bind and use texture
			texture.bind();
			this->shader->set_int("useTex", 1);

			// Draw shape
			this->vao->bind();
			if(shape == ShapeType::TRIANGLE) {
				glDrawArrays(GL_TRIANGLES, 0, 3);
			} else {
				glDrawArrays(GL_TRIANGLE_FAN, 3, 4);
			}
			this->vao->unbind();

			// Unbind texture for next shape
			this->shader->set_int("useTex", 0);
			texture.unbind();
		}

		inline void draw(const ShapeType shape, const glm::vec2 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline) {

			this->draw_2d(pos, size, color, rotate, outline);

			// Draw shape
			this->vao->bind();
			if(shape == ShapeType::TRIANGLE) {
				glDrawArrays(GL_TRIANGLES, 0, 3);
			} else {
				glDrawArrays(GL_TRIANGLE_FAN, 3, 4);
			}
			this->vao->unbind();
		}
};

