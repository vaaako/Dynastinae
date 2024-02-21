#pragma once

#include "../renderer.hpp"
#include "../../types/texture.hpp"
#include "../../types/color.hpp"

class Renderer3D : public Renderer {
	public:
		Renderer3D(const float FOV, const float near_plane, const float far_plane);

		// Texture
		inline void pyramid(const Texture& texture, const float x, const float y, const float z, const float size,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 1.0f }) {

			this->draw(ShapeType::PYRAMID, texture, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);

			// Unbind texture for next shape
			this->shader->set_int("useTex", 0);
			texture.unbind();
		}

		// Texture color first
		inline void pyramid(const Texture& texture, const float x, const float y, const float z, const float size,
				const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw(ShapeType::PYRAMID, texture, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		}

		// Rotate and Outline first
		inline void pyramid(const float x, const float y, const float z, const float size,
				const float rotate = 0.0f, const bool outline = false, const Color& color = { 0.0f, 0.0f }) {

			this->draw(ShapeType::PYRAMID, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		}

		// Color first
		inline void pyramid(const float x, const float y, const float z, const float size,
			const Color& color, const float rotate = 0.0f, const bool outline = false) {

			this->draw(ShapeType::PYRAMID, glm::vec3(x, y, z), glm::vec2(size, size), color, rotate, outline);
		}

	private:
		enum class ShapeType {
			PYRAMID,
			CUBE
		};

		const float fov;
		const float near_plane;
		const float far_plane;

		const char* vertex_shader = R"(
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

		const char* fragment_shader = R"(
			#version 330 core

			out vec4 FragColor;
			in vec2 texCoord;

			uniform int useTex = 0;
			uniform vec4 shapeColor; // Get shapeColor from vertexShader
			uniform sampler2D texSampler;

			void main() {
				if(useTex == 1) {
					FragColor = texture(texSampler, texCoord) * vec4(shapeColor.rgba);
				} else {
					FragColor = vec4(shapeColor.rgba);
				}
			}
		)";

		inline void draw(const ShapeType shape, const glm::vec3 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline) {

			this->draw_3d(pos, size, color, rotate, outline);

			// Draw shape
			this->vao->bind();
			if(shape == ShapeType::PYRAMID) {
				glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
				// glDrawArrays(GL_TRIANGLES, 0, 18);
			} else {
				glDrawArrays(GL_TRIANGLE_FAN, 5, 6);
			}
			this->vao->unbind();
		}

		inline void draw(const ShapeType shape, const Texture& texture,
				const glm::vec3 pos, glm::vec2 size,
				const Color& color, const float rotate, const bool outline) {


			this->draw_3d(pos, size, color, rotate, outline);

			// Bind and use texture
			texture.bind();
			this->shader->set_int("useTex", 1);

			this->vao->bind();
			if(shape == ShapeType::PYRAMID) {
				glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
				// glDrawArrays(GL_TRIANGLES, 0, 18);
			} else {
				glDrawArrays(GL_TRIANGLE_FAN, 5, 6);
			}
			this->vao->unbind();

			// Unbind texture for next shape
			this->shader->set_int("useTex", 0);
			texture.unbind();
		}
};

