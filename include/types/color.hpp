#pragma once

#include <glm/vec4.hpp>
#include <cmath>

struct Color {
	float r;
	float g;
	float b;
	float a;

	Color(const float r, const float g, const float b, const float a = 1.0f)
		:
			r((r < 0.0f || r > 1.0f) ? 1.0f : r),
			g((g < 0.0f || g > 1.0f) ? 1.0f : g),
			b((b < 0.0f || b > 1.0f) ? 1.0f : b),
			a((a < 0.0f || a > 1.0f) ? 1.0f : a)
		{}

	Color(float color, const float a = 1.0f) : a(a) {
		color = (color < 0.0f || color > 1.0f) ? 1.0f : color;

		this->r = color;
		this->g = color;
		this->b = color;
	}


	inline glm::vec4 to_vector4f() const {
		return glm::vec4(this->r, this->g, this->b, this->a);
	}

	inline void swap_colors(const Color& color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->a = color.a;
	}

	inline void swap_colors(const float r, const float g, const float b, const float a = 1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	inline bool empty() const {
		const float epsilon = 1e-6f;
		return std::fabs(this->r + this->g + this->b + this->a) < epsilon;
	}

	inline void reset(const float val = 1.0f) {
		this->r = val;
		this->g = val;
		this->b = val;
		this->a = val;
	}

	static Color from_rbga(const float r, const float g, const float b, const float a = 255) {
		return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}
};
