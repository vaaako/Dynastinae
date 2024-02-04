#pragma once

#include "../opengl/shader_program.hpp"
#include "../opengl/vao.hpp"
#include "../opengl/vbo.hpp"
#include "../opengl/ebo.hpp"
#include <vector>

class Triangle {
	public:
		Triangle(const float x, const float y, const float width, const float height);
		~Triangle() {
			delete vao;
			delete vbo;
			delete ebo;
			delete shader;
		}

		inline void draw() const {
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			shader->use();
			vao->bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			vao->unbind();
		}
	private:
		VAO* vao = nullptr;
		VBO* vbo = nullptr;
		EBO* ebo = nullptr;
		ShaderProgram* shader = nullptr;

		// Example shader sources (replace with your own shader code)
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