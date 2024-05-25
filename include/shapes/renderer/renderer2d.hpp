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
		Renderer2D(const uint32 width, const uint32 height);

		// TODO -- Think on a better way of drawing shapes function, because this is getting too much

		/**
		 * TRIANGLE */

		// Texture
		inline void triangle(const Texture* texture, const vec2<float>& position, const float scale, 
				const float rotate = 0.0f, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_2d(this->triangle_shape, *this->shader_texture, GL_TRIANGLES, texture, position, vec2(scale), color, rotate, draw_mode);
		}

		// Rotate and draw_mode first
		inline void triangle(const vec2<float>& position, const float scale, const float rotate = 0.0f,
				const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_2d(this->triangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, vec2(scale), color, rotate, draw_mode);
		}

		// Color first
		inline void triangle(const vec2<float>& position, const float scale,
				const Color& color, const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_2d(this->triangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, vec2(scale), color, rotate, draw_mode);
		}


		/**
		 * RECTANGLE */

		// Texture
		inline void rectangle(const Texture* texture, const vec2<float>& position, const float width, const float height,
				const float rotate = 0.0f, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_2d(this->rectangle_shape, *this->shader_texture, GL_TRIANGLES, texture, position, vec2(width, height), color, rotate, draw_mode);
		}

		// Rotate and draw_mode first
		inline void rectangle(const vec2<float>& position, const float width, const float height,
				const float rotate = 0.0f, const Color& color = { 255 }, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_2d(this->rectangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, vec2(width, height), color, rotate, draw_mode);
		}

		// Color first
		inline void rectangle(const vec2<float>& position, const float width, const float height,
			const Color& color, const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) const {

			this->draw_2d(this->rectangle_shape, *this->shader, GL_TRIANGLES, nullptr, position, vec2(width, height), color, rotate, draw_mode);
		}



		inline void draw_font(const Font& font, const vec2<float>& position) const {
			this->draw_2d(this->rectangle_shape, *this->shader_texture, GL_TRIANGLE_FAN,
				 font.texture, position, vec2(static_cast<float>(font.width), static_cast<float>(font.height)), { 255 }, 0.0f, DrawMode::FILL);
		}



		/**
		* UPDATE VIEWPORT */
		inline void update_viewport(const Window& window) {
			this->update_viewport(window.get_width(), window.get_height());
		}

		void update_viewport(const uint32 width, const uint32 height);


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
				const Texture* texture, const vec2<float>& pos, const vec2<float>& size, const Color& color = { 255 },
				const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) const;
};

