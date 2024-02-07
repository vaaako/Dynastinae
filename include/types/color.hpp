#pragma once

struct Color {
	const float r;
	const float g;
	const float b;
	const float o;

	Color(const float r, const float g, const float b, const float o = 1.0f)
		: r(r), g(g), b(b), o(o) {}
};
