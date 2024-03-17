#include "../../include/types/font.hpp"
#include "../../include/utils/string.hpp"
#include "../../include/utils/sdl.hpp"

#include <stdexcept>

Font::Font(const char* path, const std::string& text, const unsigned short size, const Color& color, const TextureFilter filter)
	: path(path), text(text), size(size), color(color), filter(filter) {

	const std::string extension = String::file_extension(std::string(path));
	if(extension != "ttf") {
		TTF_Quit();
		SDL_Quit();
		throw std::invalid_argument("Failed to load font \"" + std::string(path) + "\"\n~> Only TTF format is supported");
	}

	// Check if font exist and avoid futher fram-by-frame check
	if(TTF_OpenFont(this->path, this->size) == NULL) {
		TTF_Quit();
		SDL_Quit();
		throw std::runtime_error("Failed to load " + std::string(path) + "\n~> " + TTF_GetError());
	}


	this->set_size(size);
	this->set_color(color);
	this->set_text(text);
	this->update_texture();
}

void Font::update_texture() {
	this->font = TTF_OpenFont(this->path, this->size);
	SDL_Surface* ttf_surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->color.sdl_color());

	// Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface* surface = SDLUtils::base2_surface(ttf_surface);
	SDLUtils::flip_vertically(surface);
	SDLUtils::flip_horizontally(surface);

	this->width = surface->w;
	this->height = surface->h;

	delete this->texture; // Delete last textureto avoid memory leak
	this->texture = new Texture(surface, this->filter);

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
