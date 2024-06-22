#pragma once

#include <SDL2/SDL_pixels.h>
#include "Dynastinae/types.hpp"
#include "Dynastinae/types/vector/vec3.hpp"
#include "Dynastinae/types/vector/vec4.hpp"

struct Color {
	uint8 r = 255;
	uint8 g = 255;
	uint8 b = 255;
	uint8 a = 255;

	// TODO -- Constructor with Colors enum
	Color() = default;
	Color(const uint8 value);
	Color(const vec3<uint8>& color);
	Color(const vec4<uint8>& color);
	Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a = 255);
	Color(const Color& other) = default; // Copy constructor


	inline bool isempty() const {
		return (this->r + this->g + this->b + this->a) == 0;
	}

	inline vec4<uint8> to_vec4() const {
		return vec4(this->r, this->g, this->b, this->a);
	}

	inline SDL_Color to_sdl_color() const {
		return { static_cast<uint8>(this->r), static_cast<uint8>(this->g), static_cast<uint8>(this->b), static_cast<uint8_t>(this->a) };
	}

	static Color from_hex(const int hex_value, const uint8 alpha = 255);

	bool operator==(const Color& other) {
		return (this->r == other.r)
				&& (this->g == other.g)
				&& (this->b == other.b)
				&& (this->a == other.a);
	}

	bool operator!=(const Color& other) {
		return !(*this == other);
	}

	Color& operator=(const Color& other) {
		// Check if is not the same
		if(this != &other) {
			this->r = other.r;
			this->g = other.g;
			this->b = other.b;
			this->a = other.a;
		}
		return *this;
	}

	Color& operator=(const uint8 other) {
		this->r = other;
		this->g = other;
		this->b = other;
		this->a = other;
		return *this;
	}


};
