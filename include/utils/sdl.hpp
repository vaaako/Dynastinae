#pragma once

#include <SDL2/SDL_video.h>

namespace SDL {
	// Original code: https://stackoverflow.com/questions/65815332/flipping-a-surface-vertically-in-sdl2
	inline void flip_vertically(SDL_Surface* surface) {
		// SDL_LockSurface(surface);

		int pitch = surface->pitch; // row size

		uint8_t* temp = new uint8_t[pitch]; // Temp buffer to hold a single row
		uint8_t* pixels = static_cast<uint8_t*>(surface->pixels);

		for(int i = 0; i < surface->h / 2; i++) {
			// Get pointers to the two rows to swap
			uint8_t* top_row = pixels + i * pitch;
			uint8_t* bottom_row = pixels + (surface->h - i - 1) * pitch;
			
			// Swap bottom row to top row
			memcpy(temp, top_row, pitch);
			memcpy(top_row, bottom_row, pitch);
			memcpy(bottom_row, temp, pitch);
		}

		delete[] temp;
		// SDL_UnlockSurface(surface);
	}
};
