#pragma once

#include <SDL2/SDL_video.h>

namespace SDLUtils {
	// Original code: https://stackoverflow.com/questions/65815332/flipping-a-surface-vertically-in-sdl2
	inline void flip_vertically(SDL_Surface* surface) {
		SDL_LockSurface(surface);

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
		SDL_UnlockSurface(surface);
	}

	inline void flip_horizontally(SDL_Surface* surface) {
		SDL_LockSurface(surface);

		int pitch = surface->pitch; // row size

		uint8_t* temp = new uint8_t[pitch]; // Temp buffer to hold a single row
		uint8_t* pixels = static_cast<uint8_t*>(surface->pixels);

		int pixel_size = surface->format->BytesPerPixel;

		for(int i = 0; i < surface->h; i++) {
			// Get pointer to the row
			uint8_t* row = pixels + i * pitch;
			
			// Iterate over half of the row
			for(int j = 0; j < surface->w / 2; j++) {
				// Calculate the index of the pixel from the left and its corresponding pixel from the right
				int left_pixel_index = j * pixel_size;
				int right_pixel_index = (surface->w - j - 1) * pixel_size;
				
				// Swap the pixels
				for(int k = 0; k < pixel_size; k++) {
					std::swap(row[left_pixel_index + k], row[right_pixel_index + k]);
				}
			}
		}

		delete[] temp;
		SDL_UnlockSurface(surface);
	}


	// Original code: https://stackoverflow.com/questions/30016083/sdl2-opengl-sdl2-ttf-displaying-text
	// "So OpenGL requires that all textures have dimensions of Base2 on my system (2,4,16,32,64...)"
	inline unsigned int power_two_floor(unsigned int val) {
		unsigned int power = 2;
		unsigned int next_val = power * 2;

		while((next_val *= 2) <= val) {
			power *= 2;
		}

		return power * 2;
	}

	// Create a surface to the correct size in RGB format, and copy the old image
	inline SDL_Surface* base2_surface(SDL_Surface* surface) {
		int w = SDLUtils::power_two_floor(surface->w) * 2;
		int h = SDLUtils::power_two_floor(surface->h) * 2;

		// SDL_Surface * s = SDL_CreateRGBSurface(0, surface->w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_BlitSurface(surface, NULL, s, NULL); // Swap
		return s;
	}
};
