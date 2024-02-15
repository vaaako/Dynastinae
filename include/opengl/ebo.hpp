#pragma once

#include <GL/glew.h>
#include <vector>

class EBO {
	public:
		EBO(const std::vector<unsigned int>& indices);
		~EBO() {
			glDeleteBuffers(1, &this->id);
		}

		inline void bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
		}
	private:
		GLuint id;
};
