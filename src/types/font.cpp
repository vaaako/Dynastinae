#include "../../include/types/font.hpp"
#include "../../include/utils/string.hpp"
#include "../../include/utils/sdl.hpp"

#include <iostream>

// TODO -- Filter paramter
Font::Font(const std::string& path, const std::string& text, const unsigned short size, const Color& color) : path(path), text(text), size(size), color(color) {
	const std::string extension = String::file_extension(path);
	if(extension != "ttf") {
		SDL_Log("Unable to load font %s \n~> Only TTF is supported", path.c_str());
		TTF_Quit();
		SDL_Quit();
		return;
	}

	this->set_size(size);
	this->set_color(color);
	this->set_text(text);
	this->update_texture();
}

void Font::update_texture() {
	this->font = TTF_OpenFont(this->path.c_str(), this->size);
	if(!this->font) {
		std::cout << "Font path " + this->path << std::endl;
		SDL_Log("Unable to load font %s \n~> %s", this->path.c_str(), TTF_GetError());
		TTF_Quit();
		SDL_Quit();
		return;
	}

	SDL_Surface* ttf_surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->color.sdl_color());
	// SDL_Surface* ttf_surface = TTF_RenderUTF8_Blended(font, text.c_str(), color.sdl_color());
	if(!ttf_surface) {
		SDL_Log("Unable to create font \n~> %s", TTF_GetError());
		TTF_Quit();
		SDL_Quit();
		return;
	}

	// Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface* surface = SDLUtils::base2_surface(ttf_surface);
	SDLUtils::flip_vertically(surface);
	SDLUtils::flip_horizontally(surface);

	this->width = surface->w;
	this->height = surface->h;

	delete this->texture; // Delete last textureto avoid memory leak
	this->texture = new Texture(surface, TextureFilter::LINEAR);

	SDL_FreeSurface(ttf_surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(this->font); // WARNING -- I don't know if i should close here or in delete
}

void Font::set_text(const std::string& text) {
	this->text = text.c_str();
	this->update_texture();
}


void Font::set_color(const Color& color) {
	this->color = color;
	this->update_texture();
}


void Font::set_size(const unsigned short size) {
	this->size = size;
	this->update_texture();
}
