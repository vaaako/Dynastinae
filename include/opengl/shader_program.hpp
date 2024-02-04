#pragma once

#include "../../libs/glad/glad.h"

class ShaderProgram {
	public:
		ShaderProgram(const char* vertex_source, const char* fragment_source);
		~ShaderProgram() {
			glDeleteProgram(this->programID);
		}

		inline void use() {
			glUseProgram(this->programID);
		}
	private:
		GLuint programID;
};
