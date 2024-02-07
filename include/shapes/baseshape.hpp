#pragma once

#include "../opengl/shader_program.hpp"
#include "../opengl/vao.hpp"
#include "../opengl/vbo.hpp"
#include "../opengl/ebo.hpp"
#include <vector>


class BaseShape {
	public:
		BaseShape(const float x, const float y);

		// Only this is being used right now
		BaseShape(const float x, const float y, const std::vector<unsigned int>& indices, const std::vector<float>& colors);

		BaseShape(const float x, const float y, const std::vector<float>& vertices, 
			const std::vector<unsigned int>& indices, std::vector<float>& colors);

		// For passing non declared vectors
		BaseShape(const float x, const float y, const std::vector<float> vertices, 
			const std::vector<unsigned int> indices, std::vector<float> colors);

		~BaseShape() {
			// delete vao;
			// delete vbo;
			// delete ebo;
			// delete shader;
		}

		virtual inline void draw() {
			// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			this->shader->use();
			this->vao->bind();
			this->draw_array();
			this->vao->unbind();
		}

	protected:
		const float x;
		const float y;

		const VAO* vao = nullptr;
		VBO* vbo = nullptr; // VBO may use store_data after
		const ShaderProgram* shader = nullptr;
		virtual inline void draw_array() const = 0;

	private:
		const EBO* ebo = nullptr;

		const char* vertexShaderSource = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec3 aColor;
			
			out vec3 ourColor; // output a color to the fragment shader

			void main() {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
				ourColor = aColor; // Set ourColor to the input color got from the vertex data
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core

			out vec4 FragColor;
			in vec3 ourColor; // Get ourColor from vertexShader

			void main() {
				// FragColor = vec4(1.0, 0.5, 0.2, 1.0);
				FragColor = vec4(ourColor, 1.0);
			}
		)";
};
