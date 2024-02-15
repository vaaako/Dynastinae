#include "../../include/types/texture.hpp"

#include <SDL2/SDL_image.h>

#include <SDL2/SDL_render.h>
#include "../../include/utils/sdl.hpp"


#include <iostream>
// TODO -- texture min/max filter parameter
// TODO -- Accept JPG and PNG
//
// https://learnopengl.com/Getting-started/Textures
Texture::Texture(const char* file) {
	GLuint tex_type = GL_TEXTURE_2D; // Common
	// GLuint tex_type = GL_TEXTURE_2D_ARRAY; // Texture Atlas
	

	// Open image with SDL
	SDL_Surface* surf = IMG_Load(file);
	if(surf == NULL) {
		IMG_Quit();
		SDL_Quit();
		SDL_Log("Failed to load texture: %s", SDL_GetError());
		return;
	}

	std::cout << "Texture loaded successfully! Width: " << surf->w << ", Height: " << surf->h << ", Format: " << surf->format->BytesPerPixel << " bytes per pixel" << std::endl;
	SDL::flip_vertically(surf); // OpenGL draws image fliped, so flip before

	glGenTextures(1, &this->tex_id); // num of textures, pointer
	// glActiveTexture(GL_TEXTURE0); // Just if add support to draw multiple textures at the same time
	glBindTexture(tex_type, this->tex_id);


	// Set filter parameters
	// Nearest: Pixelate / Linear: Blur
	glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Repeat, Mirrored Repeat, Clamp to Edge, Clamp to Border (then use array of RGBA to color the border)
	glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns image to texture object
	// glTexImage3D(tex_type, 0, GL_RGBA, surf->w, surf->h, 0,
	// 	0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
	//              Pixels type      Image bytes
	// First RGBA: Desired color channels / Second RGBA: Image color channels
	//                     ^- GL_RGB: jpg/jpeg, GL_RGBA: png

	// Check before if is JPG or PNG
	glTexImage2D(tex_type, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
	// glTexImage2D(tex_type, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

	// Generate Mipmap
	glGenerateMipmap(tex_type);

	// Free surface
	SDL_FreeSurface(surf);
	IMG_Quit();

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}


// 0.0f, 0.0f, // Bottom Left Corner
// 0.0f, 1.0f, // Top Left Corner
// 1.0f, 1.0f, // Top Right Corner
// 1.0f, 0.0f, // Bottom Left Corner
