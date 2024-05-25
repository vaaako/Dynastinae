#include "../../include/types/color.hpp"

Color::Color(vec3i8& color) : r(color.x), g(color.y), b(color.z), a(255) {}
Color::Color(vec4i8& color) : r(color.x), g(color.y), b(color.z), a(color.w) {}
Color::Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a) : r(r), g(g), b(b), a(a) {}
