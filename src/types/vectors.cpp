#include "../../include/types/vectors.hpp"

Vector2f::Vector2f(const float x, const float y) : x(x), y(y) {}
Vector3f::Vector3f(const float x, const float y, const float z) : Vector2f(x, y), z(z) {}
