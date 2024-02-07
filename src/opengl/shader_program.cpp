#include "../../include/opengl/shader_program.hpp"
#include <SDL2/SDL_log.h>
#include <cstddef>

// TEST //
// const char* vertexShaderSource = R"(
// 	#version 330 core

// 	layout (location = 0) in vec3 aPos;

// 	void main() {
// 		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
// 	}
// )";

// const char* fragmentShaderSource = R"(
// 	#version 330 core

// 	out vec4 FragColor;

// 	void main() {
// 		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
// 	}
// )";
// TEST //

ShaderProgram::ShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source) {
	// Compile shaders
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	// Check vertex shader error
	GLint success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		SDL_Log("Vertex shader compilation failed: \n~> %s", info_log);
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	// Check fragment shader error
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		SDL_Log("\nFragment shader compilation failed: \n~> %s", info_log);
	}


	// Create shader program
	this->programID = glCreateProgram(); // Set program ID
	glAttachShader(this->programID, vertex_shader);
	glAttachShader(this->programID, fragment_shader);
	glLinkProgram(this->programID);

	// Check link error
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if(!success) {
		GLchar info_log[512];
		glGetProgramInfoLog(this->programID, 512, NULL, info_log);
		SDL_Log("Had error on linking shaders: \n~> %s\n", info_log);
	}

	// Not necessary anymore
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
