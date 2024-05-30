#pragma once

#include <GL/glew.h>

class VAO {
	public:
		VAO();
		~VAO() {
			glDeleteVertexArrays(1, &this->id);
		}

		inline void bind() const {
			glBindVertexArray(this->id);
		}

		inline void unbind() const {
			glBindVertexArray(0);
		}
	private:
		GLuint id;
};
