#include "../../include/types/texture.hpp"
#include "../../include/utils/sdl.hpp"

#include <SDL2/SDL_render.h>
#include <iostream> // TODO -- Remove later

Texture::Texture(const std::string& path, const TextureFilter filter, const TextureWrap wrap) : path(path) {
	// Open image with SDL
	SDL_Surface* surface = IMG_Load(path.c_str());
	if(surface == NULL) {
		SDL_Log("Failed to load texture \"%s\" \n~> %s", path.c_str(), SDL_GetError());
		IMG_Quit();
		SDL_Quit();
		return;
	}

	std::cout << "Texture loaded successfully! Width: " << surface->w << ", Height: " << surface->h << ", Format: " << surface->format->BytesPerPixel << " bytes per pixel" << std::endl;
	SDLUtils::flip_vertically(surface); // OpenGL draws image fliped, so flip before

	glGenTextures(1, &this->tex_id); // num of textures, pointer
	glBindTexture(this->tex_type, this->tex_id);


	// Set filter parameters
	// Nearest: Pixelate / Linear: Blur
	if(filter == TextureFilter::LINEAR) {
		glTexParameteri(this->tex_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(this->tex_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(this->tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(this->tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	// Repeat, Mirrored Repeat, Clamp to Edge, Clamp to Border (then use array of RGBA to color the border)
	switch (wrap) {
		case TextureWrap::REPEAT:
			glTexParameteri(this->tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(this->tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case TextureWrap::MIRRORED:
			glTexParameteri(this->tex_type, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(this->tex_type, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			break;
		case TextureWrap::CLAMP_TO_EDGE:
			glTexParameteri(this->tex_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(this->tex_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		default:
			break;
	}

	// Check before if is JPG or PNG
	GLenum texture_format = 0;
	Uint8 colors = surface->format->BytesPerPixel;

	// 4 Colors
	if(surface->format->BytesPerPixel == 4) {
		if (surface->format->Rmask == 0x000000ff) {
			texture_format = GL_RGBA;
		} else {
			texture_format = GL_BGRA;
		}
	} else {
		if(surface->format->Rmask == 0x000000ff) {
			texture_format = GL_RGB;
		} else {
			texture_format = GL_BGR;
		}
	}

	// No format found
	if(texture_format == 0) {
		SDL_Log("Failed to load texture \"%s\" \n~> Supported extensions are: PNG, JPG and JPEG", path.c_str());
		IMG_Quit();
		SDL_Quit();
		return;
	}

	// Create texture
	glTexImage2D(this->tex_type, 0, colors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	// Generate Mipmap
	glGenerateMipmap(this->tex_type);

	// Free surface
	SDL_FreeSurface(surface);
	// IMG_Quit();

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind
}


Texture::Texture(const SDL_Surface* surface, const TextureFilter filter) {
	glGenTextures(1, &this->tex_id); // num of textures, pointer
	glBindTexture(this->tex_type, this->tex_id);

	// Set filter parameters
	// Nearest: Pixelate / Linear: Blur
	if(filter == TextureFilter::LINEAR) {
		glTexParameteri(this->tex_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(this->tex_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(this->tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(this->tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	// Check before if is JPG or PNG
	GLenum texture_format = 0;
	Uint8 colors = surface->format->BytesPerPixel;

	// 4 Colors
	if(surface->format->BytesPerPixel == 4) {
		if (surface->format->Rmask == 0x000000ff) {
			texture_format = GL_RGBA;
		} else {
			texture_format = GL_BGRA;
		}
	} else {
		if(surface->format->Rmask == 0x000000ff) {
			texture_format = GL_RGB;
		} else {
			texture_format = GL_BGR;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, colors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
	// Generate Mipmap
	glGenerateMipmap(this->tex_type);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind
}


// Assigns image to texture object
// the type may beGL_TEXTURE_2D_ARRAY 
// glTexImage3D(this->tex_type, 0, GL_RGBA, surface->w, surface->h, 0,
// 	0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
//              Pixels type      Image bytes
// First RGBA: Desired color channels / Second RGBA: Image color channels
//                     ^- GL_RGB: jpg/jpeg, GL_RGBA: png
