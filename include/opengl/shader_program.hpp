#pragma once

#include "../types/vectors.hpp"

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>

class ShaderProgram {
	public:
		ShaderProgram(const char* vertex_source, const char* fragment_source);
		~ShaderProgram() {
			glDeleteProgram(this->programID);
		}

		inline void use() const {
			glUseProgram(this->programID);
		}

		inline void unbind() const {
			glUseProgram(0);
		}

		inline GLuint id() const {
			return this->programID;
		}


		/**
		 * UNIFORMS */
		inline void set_matrix4f(const char* unif, const glm::mat4& mat) const {
			GLuint loc = glGetUniformLocation(this->programID, unif);
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
		}

		inline void set_vector4f(const char* unif, const Vector4f& vec) const {
			GLuint loc = glGetUniformLocation(this->programID, unif);
			glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
		}

		inline void set_int(const char* unif, const int val) const {
			GLuint loc = glGetUniformLocation(this->programID, unif);
			glUniform1i(loc, val);
		}
	private:
		GLuint programID;
};
