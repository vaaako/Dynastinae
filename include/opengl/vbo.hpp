#pragma once

#include <GL/glew.h>
#include <vector>

class VBO {
	public:
		VBO();
		VBO(const std::vector<float>& data, const int position = 0, const int dimension = 3); // Any data as the first one
		// VBO(const std::vector<float>& vertices, const std::vector<float>& color);
		~VBO() {
			glDeleteBuffers(1, &this->id);
		}

		void store_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimensions);

		inline void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}
	private:
		GLuint id;
};
