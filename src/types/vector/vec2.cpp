#include "../../../include/types/vector/vec2.hpp"

template <typename T>
vec2<T>::vec2(T num) : x(num), y(num) {}

template <typename T>
vec2<T>::vec2(T x, T y) : x(x), y(y) {}
