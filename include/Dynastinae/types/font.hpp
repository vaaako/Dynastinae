#pragma once

#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include "Dynastinae/shapes/2d/rectangle.hpp"
#include "Dynastinae/types/color.hpp"
#include "Dynastinae/types/texture.hpp"

struct Font : public Rectangle {
	// NOTE -- Texture needs to be a pointer, when changing the texture, the old texture need to be deleted (i could solve this by adding a "change texture" method in texture.hpp, but i don't think this makes any sense)
	Font(const char* path, const std::string& text, const uint16 size = 24, const Color& color = 255, const TextureFilter filter = TextureFilter::LINEAR);
	~Font() {
		TTF_CloseFont(this->sdl_font);
	}

	void update_texture();
	void set_text(const std::string& text);
	void set_color(const Color& color);
	void set_font_size(const uint16 fsize);

	inline std::string& get_text() {
		return this->text;
	}

	inline uint64 get_size() {
		return this->fsize;
	}

	inline Color& get_color() {
		return this->color;
	}

	private:
		const char* path; // Avoid conversion each frame, since path would be used each frame using std::string would lead me converting it to char* each frame
		std::string text; // This is not char* because of convenience
		uint16 fsize;
		Color color;
		TextureFilter filter;

		TTF_Font* sdl_font = TTF_OpenFont("", 0); // Init nothing so it can free the first time without using a if-check
};
