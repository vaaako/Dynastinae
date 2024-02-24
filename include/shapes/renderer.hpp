#pragma once

#include "../opengl/shader_program.hpp"
#include "../opengl/vao.hpp"
#include "../opengl/vbo.hpp"
#include "../opengl/ebo.hpp"
#include "../types/color.hpp"
#include "../types/texture.hpp"
#include "../window/window.hpp"
#include <memory>

class Renderer {
	public:
		Renderer() = default;

		// Try this later
		// Update VBO to add a new shape
		// inline void new_shape(const std::vector<float>& vertices) {}

		// SET COLOR
		inline void set_color(const Color& color) {
			this->cur_color.change_colors(color);
		}

		inline void set_color(const float r, const float g, const float b, const float a = 1.0f) {
			this->cur_color = { r, g, b, a };
		}

		inline void use_custom_color(const std::vector<float>& color) {
			this->vbo->store_single_data(color, 2, 4);
		}
	private:
		// Just defaults for draw_3d
		const float fov = 45.0f;
		const float near_plane = 0.1f;
		const float far_plane = 100.0f;

	protected:
		/*
		- To make a custom shape
			- Make a custom renderer and place the shape with custom draw function
		*/

		std::unique_ptr<const ShaderProgram> shader = nullptr;
		std::unique_ptr<const ShaderProgram> shader_texture = nullptr;

		const std::unique_ptr<const VAO> vao = std::make_unique<VAO>(); // Make VAO right away
		std::unique_ptr<VBO> vbo = nullptr;
		std::unique_ptr<const EBO> ebo = nullptr;

		Color cur_color = { 1.0f };



		/**
		 * DRAW 2D
		 * */
		inline void draw_2d(const ShaderProgram& shader, const glm::vec2 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {

			(outline) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
				: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Back to fill mode if not set to line

			shader.use();

			glm::mat4 model = glm::mat4(1.0f);

			// Move, Resize and rotate
			model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f)); // Translate position
			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Origin from top-lef to center
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Origin back to top-left
			model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f)); // Resize

			// Apply changes
			shader.set_matrix4f("model", model);

			// If color is empty, use class color
			if(!custom_color) {
				shader.set_vector4f("shapeColor", (color.empty())
						? this->cur_color.to_vector4f() : glm::vec4(color.r, color.g, color.b, color.a));
			} else {
				shader.set_int("useCustom", 1);
			}
		}

		inline void draw_2d(const glm::vec2 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {

			this->draw_2d(*this->shader, pos, size, color, rotate, outline, custom_color);
		}

		inline void draw_2d(const Texture& texture, const glm::vec2 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {

			this->draw_2d(*this->shader_texture, pos, size, color, rotate, outline, custom_color);
			texture.bind();
		}



		/**
		 * DRAW 3D
		 * */
		inline void draw_3d(const ShaderProgram& shader, const glm::vec3 pos, const glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {
			// TODO -- Change outline to ENUM
			(outline) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
				: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Back to fill mode if not set to line

			shader.use();

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view  = glm::mat4(1.0f);
			glm::mat4 proj  = glm::mat4(1.0f);

			// Rotate on Y-Axis
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(1.0f, 1.0f, 0.0f));

			// Position
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

			// Camera
			proj = glm::perspective(glm::radians(this->fov),
					static_cast<float>(Window::static_width()) / static_cast<float>(Window::static_height()),
					this->near_plane, this->far_plane);

			// Apply changes
			shader.set_matrix4f("model", model);
			shader.set_matrix4f("view", view);
			shader.set_matrix4f("proj", proj);


			if(!custom_color) {
				// If color is empty, use class color
				shader.set_vector4f("shapeColor", (color.empty())
						? this->cur_color.to_vector4f() : glm::vec4(color.r, color.g, color.b, color.a));
			} else {
				shader.set_int("useCustom", 1);
			}
		}

		inline void draw_3d(const glm::vec3 pos, const glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {

			this->draw_3d(*this->shader, pos, size, color, rotate, outline, custom_color);
		}


		inline void draw_3d(const Texture& texture, const glm::vec3 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline, const bool custom_color = false) {

			this->draw_3d(*this->shader_texture, pos, size, color, rotate, outline, custom_color);
			texture.bind();
		}
};

