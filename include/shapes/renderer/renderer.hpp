#pragma once

#include "../../opengl/shader_program.hpp"
#include "../../types/color.hpp"
#include "../../types/vectors.hpp"
#include "../../window/window.hpp"
#include "../shape2d.hpp"
#include "../shape3d.hpp"
#include <memory>

class Renderer {
	public:
		Renderer() = default;

		// SET COLOR
		// inline void set_color(const Color& color) {
		// 	this->cur_color.swap_colors(color);
		// }
		//
		// inline void set_color(const float r, const float g, const float b, const float a = 1.0f) {
		// 	this->cur_color = { r, g, b, a };
		// }

		// inline void use_custom_color(const std::vector<float>& color) {
		// 	this->vbo->store_single_data(color, 2, 4);
		// }
	private:
		// Just defaults for draw_3d
		const float fov = 45.0f;
		const float near_plane = 0.1f;
		const float far_plane = 100.0f;

	protected:
		std::unique_ptr<const ShaderProgram> shader = nullptr;
		std::unique_ptr<const ShaderProgram> shader_texture = nullptr;

		Color cur_color = { 1.0f };


		/**
		 * DRAW 2D
		 * */
		inline void draw_2d(const Shape2D& shape, const ShaderProgram& shader, const GLenum draw_type,
				const Texture* texture, const glm::vec2 pos, glm::vec2 size, const Color& color,
				const float rotate, const bool outline) {

			// TODO -- Change outline to ENUM
			(outline) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Back to fill mode if not set to line

			shader.use();

			glm::mat4 model = glm::mat4(1.0f);

			// Move, Resize and rotate
			model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));                   // Translate position
			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Origin from top-lef to center
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Rotate
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Origin back to top-left
			model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));                     // Resize

			// Apply changes
			shader.set_matrix4f("model", model);
			shader.set_vector4f("shapeColor", glm::vec4(color.r, color.g, color.b, color.a));

			// TODO -- Think on a way of avoiding "if"
			//         + Think on something to add on shader
			if(texture != nullptr)
				texture->bind();

			shape.vao->bind();
			glDrawElements(draw_type, shape.indices_size, GL_UNSIGNED_INT, (void*)0);
			// glDrawArrays(draw_type, 0, shape.vertices_count);
		}




		/**
		 * DRAW 3D
		 * */
		inline void draw_3d(const Shape3D& shape, const ShaderProgram& shader,
				const Texture* texture, const glm::vec3 pos, const Color& color,
				const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const bool outline = false) {

			// TODO -- Change outline to ENUM
			(outline) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Back to fill mode if not set to line

			shader.use();

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view  = glm::mat4(1.0f);
			glm::mat4 proj  = glm::mat4(1.0f);

			// Rotate on Y-Axis
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(axis.x, axis.y, axis.z));

			// Position
			// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
			view = glm::translate(view, glm::vec3(pos.x, pos.y, pos.z));

			// Camera
			proj = glm::perspective(glm::radians(this->fov),
					static_cast<float>(Window::static_width()) / static_cast<float>(Window::static_height()),
					this->near_plane, this->far_plane);

			// Apply changes
			shader.set_matrix4f("model", model);
			shader.set_matrix4f("view", view);
			shader.set_matrix4f("proj", proj);

			shader.set_vector4f("shapeColor", glm::vec4(color.r, color.g, color.b, color.a));

			// TODO -- Think on a way of avoiding "if"
			//         + Think on something to add on shader
			if(texture != nullptr)
				texture->bind();

			shape.vao->bind();
			glDrawElements(GL_TRIANGLES, shape.indices_size, GL_UNSIGNED_INT, (void*)0);
		}

/*
		// Get camera position/rotation
		rotation = camera.getRotation();
		position = camera.getPosition();

		// System.out.println("X: " + position.x + " Y: " + position.y + " Z: " + position.z);
		
		// Projection Matrix //
		pMatrix.identity(); // Create matrix
		pMatrix.perspective((float) Math.toRadians(camera.getFovDeg()), (float)camera.getWidth() / camera.getHeight(), nearPlane, farPlane); // Adds perspective to the scene

		// Model view matrix //
		mvMatrix.identity();
		rotate2D(mvMatrix, (float) (rotation.x + Math.TAU / 4), (float) rotation.y);
		mvMatrix.translate(-position.x, -position.y, -position.z); // Move camera (minus = away, positive = zoom)	

		// Exports the camera amtrix to the Vertex Shader (proj * view)
		shaderProgram.uniformMatrix(shaderProgram.findUniform("camMatrix"), pMatrix.mul(mvMatrix));
*/
};

