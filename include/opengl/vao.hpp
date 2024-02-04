#pragma once

#include "../../libs/glad/glad.h"

class VAO {
	public:
		VAO();
		~VAO() {
			glDeleteVertexArrays(1, &this->id);
		}

		inline void bind() {
			glBindVertexArray(this->id);
		}

		inline void unbind() {
			glBindVertexArray(0);
		}
	private:
		GLuint id;
};