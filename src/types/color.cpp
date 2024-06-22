#include "Dynastinae/types/color.hpp"

Color::Color(const vec3<uint8>& color) : r(color.x), g(color.y), b(color.z), a(255) {}
Color::Color(const vec4<uint8>& color) : r(color.x), g(color.y), b(color.z), a(color.w) {}
Color::Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a) : r(r), g(g), b(b), a(a) {}
Color::Color(const uint8 value) : r(value), g(value), b(value), a(value) {}

// Color::Color(const Color& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}


Color Color::from_hex(const int hex_value, const uint8 alpha) {
	const int rr = ((hex_value >> 16) & 0xFF);
	const int gg = ((hex_value >> 8) & 0xFF);
	const int bb = (hex_value & 0xFF);

	return Color(static_cast<uint8>(rr), static_cast<uint8>(gg), static_cast<uint8>(bb), alpha);
}
