#pragma once

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>
#include "Dynastinae/types/vector/vec4.hpp"

struct ShaderProgram {
		ShaderProgram(const char* vertex_source, const char* fragment_source);
		~ShaderProgram() {
			glDeleteProgram(this->id);
		}

		inline void use() const {
			glUseProgram(this->id);
		}

		inline void unbind() const {
			glUseProgram(0);
		}


		/**
		 * UNIFORMS */
		inline void set_matrix4f(const char* unif, const glm::mat4& mat) const {
			GLuint loc = glGetUniformLocation(this->id, unif);
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
		}

		inline void set_vector4f(const char* unif, const vec4<float>& vec) const {
			GLuint loc = glGetUniformLocation(this->id, unif);
			glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
		}

		inline void set_int(const char* unif, const GLuint val) const {
			GLuint loc = glGetUniformLocation(this->id, unif);
			glUniform1i(loc, val);
		}
	private:
		GLuint id;
};
