#pragma once

#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <string>

// Size need to be multiple of 2
// 16x16, 32x32, 64x64, 128x128, 256x256 etc

enum class TextureFilter {
	NEAREST =  9728,
	LINEAR = 9729
};

enum class TextureWrap {
	REPEAT = 10497,
	MIRRORED = 33648,
	CLAMP_TO_EDGE = 33071
};

struct Texture {
	Texture(const std::string& path, const TextureFilter filter = TextureFilter::LINEAR, const TextureWrap wrap = TextureWrap::REPEAT);
	Texture(const SDL_Surface* surface, const TextureFilter filter = TextureFilter::LINEAR); // NOTE -- This probably will just be used for Fonts
	~Texture() {
		glDeleteTextures(1, &this->id);
	}

	inline void bind() const {
		glBindTexture(this->tex_type, this->id);
	}

	inline void unbind() const {
		glBindTexture(this->tex_type, 0);
	}

	private:
		GLuint id;
		GLuint tex_type = GL_TEXTURE_2D; // Common
		// GL_TEXTURE_2D_ARRAY; // Texture Atlas
		const std::string path;
};


