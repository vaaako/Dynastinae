#include "Dynastinae/types/font.hpp"
#include "Dynastinae/utils/string.hpp"
#include "Dynastinae/utils/sdl.hpp"

#include <SDL2/SDL_ttf.h>
#include <stdexcept>

Font::Font(const char* path, const std::string& text, const uint16 size, const Color& color, const TextureFilter filter)
	: path(path), text(text), fsize(size), color(color), filter(filter) {

	// Check extension
	const std::string extension = StringHelper::file_extension(std::string(path));
	if(extension != "ttf") {
		TTF_Quit();
		SDL_Quit();
		throw std::invalid_argument("Failed to load font \"" + std::string(path) + "\"\n~> Only TTF format is supported");
	}

	// Check if font exist and avoid futher fram-by-frame check
	if(TTF_OpenFont(this->path, this->fsize) == NULL) {
		TTF_Quit();
		SDL_Quit();
		throw std::runtime_error("Failed to load " + std::string(path) + "\n~> " + TTF_GetError());
	}

	// Config font
	this->set_size(size);
	this->set_color(color);
	this->set_text(text);
	this->update_texture();
}

void Font::update_texture() {
	// Delete old sdl font
	TTF_CloseFont(this->sdl_font);

	this->sdl_font = TTF_OpenFont(this->path, this->fsize);
	SDL_Surface* ttf_surface = TTF_RenderText_Blended(this->sdl_font, this->text.c_str(), this->color.to_sdl_color());

	// Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface* surface = SDLHelper::base2_surface(ttf_surface);
	SDLHelper::flip_vertically(surface);
	SDLHelper::flip_horizontally(surface);

	// Set Size
	this->set_size({ static_cast<float>(surface->w), static_cast<float>(surface->h) });

	// Delete old texture to avoid memory leak
	this->set_texture(new Texture(surface, this->filter));

	// Free surfaces
	SDL_FreeSurface(ttf_surface);
	SDL_FreeSurface(surface);
}



void Font::set_text(const std::string& text) {
	this->text = text;
	this->update_texture();
}

void Font::set_color(const Color& color) {
	this->color = color;
	this->update_texture();
}

void Font::set_font_size(const uint16 fsize) {
	this->fsize = fsize;
	this->update_texture();
}


