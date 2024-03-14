#pragma once

#include <GL/glew.h>
#include <vector>

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

		void store_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimension, const unsigned int total_dimensions, const void* offset);
		void link_attrib(const unsigned int position, const unsigned int dimension, const unsigned int total_dimensions, const void* offset);
		void store_two_fields_data(const std::vector<float>& data, const unsigned int pos_dim, const unsigned int tex_dim, const unsigned int vertex1 = 0, const unsigned int vertex2 = 1);
		
	private:
		GLuint id;
		// long unsigned int size = 0; // INFO -- I don't think i will be using this
};
