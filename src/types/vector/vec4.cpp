#include "../../../include/types/vector/vec4.hpp"

template <typename T>
vec4<T>::vec4(T num) : x(num), y(num), z(num), w(num) {}

template <typename T>
vec4<T>::vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
