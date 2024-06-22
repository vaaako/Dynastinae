#include "Dynastinae/opengl/shader_program.hpp"
#include "Dynastinae/utils/log.hpp"
#include <cstddef>

ShaderProgram::ShaderProgram(const char* vertex_source, const char* fragment_source) {
	this->make_program(vertex_source, fragment_source);
}

ShaderProgram::ShaderProgram(const std::string& vertex_source, const std::string& fragment_source) {
	this->make_program(vertex_source.c_str(), fragment_source.c_str());
}

void ShaderProgram::make_program(const char* vertex_source, const char* fragment_source) {
	// Compile shaders
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
	glCompileShader(vertex_shader);

	// Check vertex shader error
	GLint success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		LOG_ERROR("Vertex shader compilation failed: %s", info_log);
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
	glCompileShader(fragment_shader);

	// Check fragment shader error
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		LOG_ERROR("Fragment shader compilation failed: %s", info_log);
	}


	// Create shader program
	this->id = glCreateProgram(); // Set program ID
	glAttachShader(this->id, vertex_shader);
	glAttachShader(this->id, fragment_shader);
	glLinkProgram(this->id);

	// Check link error
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if(!success) {
		GLchar info_log[512];
		glGetProgramInfoLog(this->id, 512, NULL, info_log);
		LOG_ERROR("Had error on linking shaders: %s", info_log);
	}

	// Not necessary anymore
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
