#pragma once

#include <SDL2/SDL_video.h>
#include "Dynastinae/types/default.hpp"

// TODO -- Unify flip vertically and horizontally?
namespace SDLHelper {
	// Original code: https://stackoverflow.com/questions/65815332/flipping-a-surface-vertically-in-sdl2
	void flip_vertically(SDL_Surface* surface);
	void flip_horizontally(SDL_Surface* surface);

	// Original code: https://stackoverflow.com/questions/30016083/sdl2-opengl-sdl2-ttf-displaying-text
	// "So OpenGL requires that all textures have dimensions of Base2 on my system (2,4,16,32,64...)"
	uint32 power_two_floor(uint32 val);

	// Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface* base2_surface(SDL_Surface* surface);
};
