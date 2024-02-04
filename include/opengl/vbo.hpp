#pragma once

#include "../../libs/glad/glad.h"
#include <vector>

class VBO {
	public:
		VBO(const std::vector<float>& vertices);
		VBO(const std::vector<float>& vertices, const std::vector<float>& color);
		~VBO() {
			glDeleteBuffers(1, &this->id);
		}

		void store_data(const unsigned int position, const unsigned int dimensions, const std::vector<float>& data);

		inline void bind() {
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}
	private:
		GLuint id;
};