#pragma once

#include <GL/glew.h>
#include <vector>

class VBO {
	public:
		VBO();
		VBO(const std::vector<float>& data, const int position = 0, const int dimension = 3); // Any data

		~VBO() {
			glDeleteBuffers(1, &this->id);
		}

		inline void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}

		void store_single_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimensions);
		void store_data(const std::vector<float>& data, const std::vector<float>& data2, const unsigned int dimensions1, const unsigned int dimensions2);
		void store_data(const std::vector<float>& data, const unsigned int dimension1, const unsigned int dimension2);
		void store_data(const std::vector<float>& data, const unsigned int vertex_start, const std::vector<unsigned int> dimensions);
		
		void store_data(const std::vector<float>& data, const std::vector<float>& sub_data,
				const std::vector<float>& data2, const std::vector<float>& sub_data2,
				const unsigned int field1_dimensions, const unsigned int field2_dimensions);
	private:
		GLuint id;
		long unsigned int vbo_size = 0; // INFO -- Maybe this will be used somewhere at some point
};
