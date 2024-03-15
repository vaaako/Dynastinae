#include "../../include/types/vectors.hpp"

Vector2f::Vector2f(const float x, const float y) : x(x), y(y) {}
Vector3f::Vector3f(const float x, const float y, const float z) : Vector2f(x, y), z(z) {}
Vector4f::Vector4f(const float x, const float y, const float z, const float w) : Vector3f(x, y, z), w(w) {}
Vector5f::Vector5f(const float x, const float y, const float z, const float w, const float h) : Vector4f(x, y, z, w), h(h) {}
