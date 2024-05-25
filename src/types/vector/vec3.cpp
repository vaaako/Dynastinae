#include "../../../include/types/vector/vec3.hpp"

template <typename T>
vec3<T>::vec3(T num) : x(num), y(num), z(num) {}

template <typename T>
vec3<T>::vec3(T x, T y, T z) : x(x), y(y), z(z) {}
