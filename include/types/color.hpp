#pragma once

struct Color {
	const float r;
	const float g;
	const float b;
	const float a;

	Color(const float r, const float g, const float b, const float a = 1.0f)
		: r(r), g(g), b(b), a(a) {}
};
