#pragma once

#include <GL/glew.h>
#include <vector>

class EBO {
	public:
		EBO(const std::vector<unsigned int>& indices);
		EBO(const std::vector<unsigned int>& indices, const std::vector<unsigned int>& indices2);
		~EBO() {
			glDeleteBuffers(1, &this->id);
		}

		inline void bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
		}

		inline void unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	private:
		GLuint id;
};
