#include "../../../include/types/vector/vec6.hpp"

template <typename T>
vec6<T>::vec6(T num) : x(num), y(num), z(num), u(num), v(num), w(num) {}

template <typename T>
vec6<T>::vec6(T x, T y, T z, T u, T v, T w) : x(x), y(y), z(z), u(u), v(v), w(w) {}
