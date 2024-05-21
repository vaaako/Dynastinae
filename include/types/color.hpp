#pragma once

#include "vectors.hpp"
#include <SDL2/SDL_pixels.h>

// Fill more
enum ColorsEnum {
	RED = 0xff0000,
	BLUE = 0x00ff00,
	GREEN = 0x0000ff
};

struct Color {
	unsigned char r = 255;
	unsigned char g = 255;
	unsigned char b = 255;
	unsigned char a = 255;

	// TODO -- Constructor with Colors enum
	Color() = default;
	Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 255)
		: r(r), g(g), b(b), a(a) {}

	Color(unsigned char color, const unsigned char alpha = 255) {
		this->r = color;
		this->g = color;
		this->b = color;
		this->a = alpha;
	}
	// Copy constructor
	Color(const Color& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
	}

	Color& operator=(const Color& other) {
		// Check if is not the same
		if (this != &other) {
			this->r = other.r;
			this->g = other.g;
			this->b = other.b;
			this->a = other.a;
		}
		return *this;
	}


	Color operator+(const Color& other) {
		return Color(this->r + other.r, this->g + other.g, this->b + other.b);
	}

	Color operator-(const Color& other) {
		return Color(this->r - other.r, this->g - other.g, this->b - other.b);
	}

	Color operator*(const Color& other) {
		return Color(this->r * other.r, this->g * other.g, this->b * other.b);
	}

	Color operator/(const Color& other) {
		return Color(this->r / other.r, this->g / other.g, this->b / other.b);
	}

	bool operator==(const Color& other) {
		return (this->r == other.r)
				&& (this->g == other.g)
				&& (this->b == other.b)
				&& (this->a == other.a);
	}



	inline void reset(const unsigned char value = 255) {
		this->r = value;
		this->g = value;
		this->b = value;
		this->a = value;
	}

	inline bool isempty() const {
		return (this->r + this->g + this->b + this->a) == 0;
	}


	inline Vector4f to_vector4f() const {
		return Vector4f(this->r, this->g, this->b, this->a);
	}

	inline SDL_Color to_sdl_color() const {
		return { static_cast<uint8_t>(this->r), static_cast<uint8_t>(this->g), static_cast<uint8_t>(this->b), static_cast<uint8_t>(this->a) };
	}

	static Color from_hex(const int hex_value, const unsigned char alpha = 255) {
		const int rr = ((hex_value >> 16) & 0xFF);
		const int gg = ((hex_value >> 8) & 0xFF);
		const int bb = (hex_value & 0xFF);

		return Color(static_cast<unsigned char>(rr), static_cast<unsigned char>(gg), static_cast<unsigned char>(bb), alpha);
	}
};
