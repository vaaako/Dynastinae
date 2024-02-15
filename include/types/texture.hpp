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
	private:
		GLuint tex_id;
};


