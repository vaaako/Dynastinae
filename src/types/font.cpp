#include "../../include/types/font.hpp"
#include "../../include/utils/string.hpp"
#include "../../include/utils/sdl.hpp"



// TODO -- Filter paramter
Font::Font(const std::string& path, const std::string& text, const unsigned short size, const Color& color) : path(path), text(text), size(size), color(color) {
	const std::string extension = String::file_extension(path);
	if(extension != "ttf") {
		SDL_Log("Unable to load font %s \n~> Only TTF is supported", path.c_str());
		TTF_Quit();
		SDL_Quit();
		return;
	}

	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	if(!font) {
		SDL_Log("Unable to load font %s \n~> %s", path.c_str(), TTF_GetError());
		TTF_Quit();
		SDL_Quit();
		return;
	}

	SDL_Surface* ttf_surface = TTF_RenderText_Blended(font, text.c_str(), color.sdl_color());

	// SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color.sdl_color());
	if(!ttf_surface) {
		SDL_Log("Unable to create font %s \n~> %s", path.c_str(), TTF_GetError());
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
	this->texture = new Texture(surface, TextureFilter::LINEAR);

	SDL_FreeSurface(ttf_surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font); // WARNING -- I don't know if i should close here or in delete
}
