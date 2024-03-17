#pragma once

#include "color.hpp"
#include "texture.hpp"

#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <string>

struct Font {
	// const std::string path;
	const char* path; // NOTE -- If font changes any element, frame-by-frame it loads from path, if it was a std::string a conversion would be done frame-by-frame
	std::string text;
	unsigned short size;
	Color color;
	TextureFilter filter;

	Texture* texture = nullptr;
	TTF_Font* font;

	// Necessary to draw
	int width;
	int height;


	Font(const char* path, const std::string& text, const unsigned short size = 24, const Color& color = { 255 }, const TextureFilter filter = TextureFilter::LINEAR);
	~Font() {
		TTF_CloseFont(this->font);
		delete texture;
	}

	void update_texture();
	void set_text(const std::string& text);
	void set_color(const Color& color);
	void set_size(const unsigned short size);
};
