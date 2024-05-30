#pragma once

#include <GL/glew.h>
#include <vector>
#include "Dynastinae/types/default.hpp"

class EBO {
	public:
		EBO(const std::vector<uint32>& indices);
		EBO(const std::vector<uint32>& indices, const std::vector<uint32>& indices2);
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
