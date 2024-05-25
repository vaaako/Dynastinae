#include "../../../include/types/vector/vec5.hpp"

template <typename T>
vec5<T>::vec5(T num) : x(num), y(num), z(num), w(num), h(num) {}

template <typename T>
vec5<T>::vec5(T x, T y, T z, T w, T h) : x(x), y(y), z(z), w(w), h(h) {}
