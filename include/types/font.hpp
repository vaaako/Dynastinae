#pragma once

#include "color.hpp"
#include "texture.hpp"

#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <string>

struct Font {
	// Necessary to draw
	int width;
	int height;
	Texture* texture = nullptr; // Texture needs to be a pointer, when changing the texture, the old texture need to be deleted (i could solve this by adding a "change texture" method in texture.hpp, but i don't think this makes any sense)

	Font(const char* path, const std::string& text, const unsigned short size = 24, const Color& color = { 255 }, const TextureFilter filter = TextureFilter::LINEAR);
	~Font() {
		TTF_CloseFont(this->sdl_font);
		delete texture;
	}

	void update_texture();
	void set_text(const std::string& text);
	void set_color(const Color& color);
	void set_size(const unsigned short size);

	private:
		const char* path; // NOTE -- If font changes any element, frame-by-frame it loads from path, if it was a std::string a conversion would be done each frame
		std::string text;
		unsigned short size;
		Color color;
		TextureFilter filter;

		TTF_Font* sdl_font;
};
