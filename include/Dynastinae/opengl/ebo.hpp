#pragma once

#include <GL/glew.h>
#include <vector>
#include "Dynastinae/types.hpp"

class EBO {
	public:
		EBO(const std::vector<uint32>& indices);
		EBO(const std::vector<uint16>& indices);
		EBO(const std::vector<uint32>& indices, const std::vector<uint32>& indices2);
		~EBO() {
			glDeleteBuffers(1, &this->id);
		}

		inline void unbind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	private:
		GLuint id;
};
