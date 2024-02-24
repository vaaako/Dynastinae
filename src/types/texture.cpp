#include "../../include/types/texture.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include "../../include/utils/sdl.hpp"
#include "../../include/utils/string.hpp"

#include <iostream> // Remove later
// TODO -- texture min/max filter parameter
// TODO -- Accept JPG and PNG
//
// https://learnopengl.com/Getting-started/Textures


Texture::Texture(const std::string& file, const TextureFilter filter, const TextureWrap wrap) {
	// Open image with SDL
	SDL_Surface* surf = IMG_Load(file.c_str());
	if(surf == NULL) {
		IMG_Quit();
		SDL_Quit();
		SDL_Log("Failed to load texture \"%s\" \n%s", file.c_str(), SDL_GetError());
		return;
	}

	std::cout << "Texture loaded successfully! Width: " << surf->w << ", Height: " << surf->h << ", Format: " << surf->format->BytesPerPixel << " bytes per pixel" << std::endl;
	SDL::flip_vertically(surf); // OpenGL draws image fliped, so flip before

	glGenTextures(1, &this->tex_id); // num of textures, pointer
	glBindTexture(this->tex_type, this->tex_id);
	// glActiveTexture(GL_TEXTURE0); // Just if add support to draw multiple textures at the same time


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
	const std::string extension = String::file_extension(file);
	if(extension == "png") {
		glTexImage2D(this->tex_type, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

	} else if(extension == "jpg" || extension == "jpeg") {
		glTexImage2D(this->tex_type, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);

	} else {
		IMG_Quit();
		SDL_Quit();
		SDL_Log("Failed to load texture \"%s\" \nExtensions supported are: PNG, JPG and JPEG", file.c_str());
		return;
	}


	// Generate Mipmap
	glGenerateMipmap(this->tex_type);

	// Free surface
	SDL_FreeSurface(surf);
	IMG_Quit();

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}



// Assigns image to texture object
// the type may beGL_TEXTURE_2D_ARRAY 
// glTexImage3D(this->tex_type, 0, GL_RGBA, surf->w, surf->h, 0,
// 	0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
//              Pixels type      Image bytes
// First RGBA: Desired color channels / Second RGBA: Image color channels
//                     ^- GL_RGB: jpg/jpeg, GL_RGBA: png
