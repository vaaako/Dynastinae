#pragma once

#include <GL/glew.h>
#include <vector>
#include "../types/default.hpp"

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

		void store_data(const std::vector<float>& data, const uint32 position, const uint32 dimension, const uint32 total_dimensions, const void* offset);
		void link_attrib(const uint32 position, const uint32 dimension, const uint32 total_dimensions, const void* offset);
		void store_two_fields_data(const std::vector<float>& data, const uint32 pos_dim, const uint32 tex_dim, const uint32 vertex1 = 0, const uint32 vertex2 = 1);
		
	private:
		GLuint id;
		// long uint32 size = 0; // INFO -- I don't think i will be using this
};
