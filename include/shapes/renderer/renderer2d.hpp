#pragma once

#include "../../types/font.hpp"
#include "../2d/triangle.hpp"
#include "../2d/rectangle.hpp"
#include "renderer.hpp"

/* TODO 

	void rectangle(Rectangle& rectangle) {
		...
	}

*/

class Renderer2D : public Renderer {
	public:
		Renderer2D(const Window& window);
		Renderer2D(const unsigned int width, const unsigned int height);

		// TODO -- Think on a better way of drawing shapes function, because this is getting too much

		/**
		 * TRIANGLE */

		// Texture
		inline void triangle(const Texture* texture, const Vector2f position, const float size, 
				const float rotate = 0.0f, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_2d(this->triangle_shape, *this->shader_texture, GL_TRIANGLES, texture, position, Vector2f(size, size), color, rotate, draw_mode);
		}

		// Rotate and draw_mode first
		inline void triangle(const Vector2f position, const float size, const float rotate = 0.0f,
				const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_2d(this->triangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, Vector2f(size, size), color, rotate, draw_mode);
		}

		// Color first
		inline void triangle(const Vector2f position, const float size,
				const Color& color, const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_2d(this->triangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, Vector2f(size, size), color, rotate, draw_mode);
		}


		/**
		 * RECTANGLE */

		// Texture
		inline void rectangle(const Texture* texture, const Vector2f position, const float width, const float height,
				const float rotate = 0.0f, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_2d(this->rectangle_shape, *this->shader_texture, GL_TRIANGLES, texture, position, Vector2f(width, height), color, rotate, draw_mode);
		}

		// Rotate and draw_mode first
		inline void rectangle(const Vector2f position, const float width, const float height,
				const float rotate = 0.0f, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_2d(this->rectangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, Vector2f(width, height), color, rotate, draw_mode);
		}

		// Color first
		inline void rectangle(const Vector2f position, const float width, const float height,
			const Color& color, const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) {

			this->draw_2d(this->rectangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, Vector2f(width, height), color, rotate, draw_mode);
		}



		inline void draw_font(const Font& font, const Vector2f position) {
			this->draw_2d(this->rectangle_shape, *this->shader_texture, GL_TRIANGLE_FAN,
				 font.texture, position, Vector2f((float)font.width, (float)font.height), { 255 }, 0.0f, DrawMode::FILL);
		}



		/**
		* UPDATE VIEWPORT */
		inline void update_viewport(const Window& window) {
			this->update_viewport(window.get_width(), window.get_height());
		}

		void update_viewport(const unsigned int width, const unsigned int height);


	private:
		// Shapes
		Triangle triangle_shape = Triangle();
		Rectangle rectangle_shape = Rectangle();

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


		void draw_2d(const Shape2D& shape, const ShaderProgram& shader, const GLenum draw_type,
				const Texture* texture, const Vector2f pos, Vector2f size, const Color& color = { 255 },
				const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) const;
};

