#pragma once

#include <GL/glew.h>

class ShaderProgram {
	public:
		ShaderProgram(const char* vertex_source, const char* fragment_source);
		~ShaderProgram() {
			glDeleteProgram(this->programID);
		}

		inline void use() const {
			glUseProgram(this->programID);
		}

		inline GLuint id() const {
			return this->programID;
		}
	private:
		GLuint programID;
};
