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

	int width;
	int height;

	Font(const std::string& path, const std::string& text, const unsigned short size = 24, const Color& color = { 255 });
	~Font() {
		// TTF_CloseFont(this->font);
		delete texture;
	}


	inline void set_text(const std::string& text) {
		this->text = text;
	}

	inline void set_size(const unsigned short size) {
		this->size = size;
	}

	inline void set_color(const Color& color) {
		this->color = color;
	}
};
