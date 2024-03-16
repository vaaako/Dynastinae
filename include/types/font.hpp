#pragma once

#include "color.hpp"
#include "texture.hpp"

#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <string>


// TODO -- Update method for text, size and color
struct Font {
	const std::string path;
	std::string text;
	unsigned short size;
	Color color;
	Texture* texture = nullptr;
	TTF_Font* font;

	// Necessary to draw
	int width;
	int height;

	Font(const std::string& path, const std::string& text, const unsigned short size = 24, const Color& color = { 255 });
	~Font() {
		TTF_CloseFont(this->font);
		delete texture;
	}

	void update_texture();
	void set_text(const std::string& text);
	void set_color(const Color& color);
	void set_size(const unsigned short size);
};
