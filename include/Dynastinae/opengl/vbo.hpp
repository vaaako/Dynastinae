#pragma once

#include <GL/glew.h>
#include "Dynastinae/types.hpp"

class VBO {
	public:
		VBO();

		~VBO() {
			glDeleteBuffers(1, &this->id);
		}

		inline void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}

		inline void unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void alloc_data(const uint64 size, const void* data);
		void link_attrib(const uint32 vertex, const uint32 dimension, const int total_byte_size, const uint32 offset);
	private:
		GLuint id;
};
