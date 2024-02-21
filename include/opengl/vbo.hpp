#pragma once

#include <GL/glew.h>
#include <vector>

class VBO {
	public:
		VBO();
		VBO(const std::vector<float>& data, const int position = 0, const int dimension = 3); // Any data
		VBO(const std::vector<float>& vertices, const std::vector<float>& color, const unsigned int vertices_dimension = 2);

		~VBO() {
			glDeleteBuffers(1, &this->id);
		}


		void store_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimensions);
		void store_data(const std::vector<float>& data, const std::vector<float>& data2, const unsigned int dimensions);

		void store_two_data(const std::vector<float>& data, const unsigned int dimension1, const unsigned int dimension2);

		inline void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}
	private:
		GLuint id;
};
