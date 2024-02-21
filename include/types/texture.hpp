#pragma once

#include <GL/glew.h>

// Size need to be multiple of 2
// 16x16, 32x32, 64x64, 128x128, 256x256 etc
class Texture {
	public:
		Texture(const char* file);

		inline GLuint id() const {
			return tex_id;
		}

		inline void bind() const {
			glBindTexture(this->tex_type, this->tex_id);
		}

		inline void unbind() const {
			glBindTexture(this->tex_type, 0);
		}
	private:
		GLuint tex_id;

		GLuint tex_type = GL_TEXTURE_2D; // Common
		// GLuint tex_type = GL_TEXTURE_2D_ARRAY; // Texture Atlas
};


