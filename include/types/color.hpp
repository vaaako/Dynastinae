#pragma once

struct Color {
	const float r;
	const float g;
	const float b;
	const float a;

	Color(const float r, const float g, const float b, const float a = 1.0f)
		:
			r((r < 0.0f || r > 1.0f) ? 1.0f : r),
			g((g < 0.0f || g > 1.0f) ? 1.0f : g),
			b((b < 0.0f || b > 1.0f) ? 1.0f : b),
			a((a < 0.0f || a > 1.0f) ? 1.0f : a)
		{}

	static Color from_rbga(const float r, const float g, const float b, const float a = 255) {
		return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}
};
