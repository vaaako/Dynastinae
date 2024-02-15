#pragma once

#include "../opengl/shader_program.hpp"
#include "../opengl/vao.hpp"
#include "../opengl/vbo.hpp"
#include "../opengl/ebo.hpp"
#include "../types/texture.hpp"
#include <memory>
#include <vector>

class Shape2D {
	public:
		Shape2D(const float x, const float y, const std::vector<unsigned int>& indices);
		Shape2D(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors); // Be sure colors has the right amount of vertices

		~Shape2D() = default;

		virtual inline void draw(const bool outline = false) {
			(outline) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
				: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Back to fill mode if not set to line

			this->shader->use();

			// Use texture if have
			if(this->texture != nullptr) {
				glBindTexture(GL_TEXTURE_2D, this->texture->id());
			}

			this->vao->bind();
			glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
			this->vao->unbind();
		}


		// TODO -- Fix for triangle
		virtual inline void bind_texture(const Texture& texture) {
			const std::vector<float> tex_array = {
				0.0f, 0.0f, // Bottom Left Corner
				1.0f, 0.0f, // Top Left Corner
				1.0f, 1.0f, // Top Right Corner
				0.0f, 1.0f  // Bottom Left Corner
			};

			this->vbo->store_data(tex_array, 2, 2);
			this->texture = std::make_unique<const Texture>(texture);

			// Just if add support to draw multiple textures at the same time
			// GLuint tex0Uni = glGetUniformLocation(this->shader->id(), "tex0");
			// this->shader->use();
			// glUniform1i(tex0Uni, 0);
		}

	protected:
		// Shape basic info
		const float x;
		const float y;
		const unsigned int indices_size;

		// VBO may use store_data later
		std::unique_ptr<VBO> vbo;

		// Make VAO right away
		const std::unique_ptr<const VAO> vao = std::make_unique<VAO>(); 

		// Will be created later
		std::unique_ptr<const ShaderProgram> shader = nullptr; // If try to make ShaderProgram here, the shaders will not be initialized yet
		std::unique_ptr<const Texture> texture = nullptr;

		// virtual inline void draw_array() const = 0;
	private:
		std::unique_ptr<const EBO> ebo = nullptr;


		// Shaders with support to texture
		const char* vertexShaderSource = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;
			layout (location = 2) in vec2 aTex;

			out vec2 texCoord;
			out vec4 shapeColor; // Output a color to the fragment shader

			void main() {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
				shapeColor  = aColor; // Set shapeColor to the input color got from the vertex data
				texCoord    = aTex;
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core

			out vec4 FragColor;
			in vec4 shapeColor; // Get shapeColor from vertexShader
			in vec2 texCoord;

			uniform sampler2D texSampler;

			void main() {

				// Check if texCoord is uninitialized (e.g., set to (0,0))
				if(texCoord == vec2(0.0)) {
					FragColor = vec4(shapeColor.rgba);
				} else {
					// TODO -- Full white is not working so well (i don't know why)
				
					FragColor = texture(texSampler, texCoord) * vec4(shapeColor.rgba);  
					// FragColor = texture(texSampler, texCoord);
				}


			}
		)";
};
