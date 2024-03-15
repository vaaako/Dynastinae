#pragma once

#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <string>

// Size need to be multiple of 2
// 16x16, 32x32, 64x64, 128x128, 256x256 etc

enum class TextureFilter {
	NEAREST,
	LINEAR
};

enum class TextureWrap {
	REPEAT,
	MIRRORED,
	CLAMP_TO_EDGE
};

struct Texture {
	GLuint tex_id;
	GLuint tex_type = GL_TEXTURE_2D; // Common
	// GL_TEXTURE_2D_ARRAY; // Texture Atlas
	const std::string path;


	Texture(const std::string& path, const TextureFilter filter = TextureFilter::LINEAR, const TextureWrap wrap = TextureWrap::REPEAT);
	Texture(const SDL_Surface* surface, const TextureFilter filter = TextureFilter::LINEAR); // NOTE -- This probably will just be used for Fonts
	~Texture() {
		glDeleteTextures(1, &this->tex_id);
	}


	inline GLuint id() const {
		return tex_id;
	}

	inline void bind() const {
		glBindTexture(this->tex_type, this->tex_id);
	}

	inline void unbind() const {
		glBindTexture(this->tex_type, 0);
	}
};


