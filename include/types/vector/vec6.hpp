#pragma once

template <typename T>
struct vec6 {
	T x = 0;
	T y = 0;
	T z = 0;
	T u = 0;
	T v = 0;
	T w = 0;

	vec6() = default;
	vec6(T num) : x(num), y(num), z(num), u(num), v(num), w(num) {}
	vec6(T x, T y, T z, T u, T v, T w) : x(x), y(y), z(z), u(u), v(v), w(w) {}
	vec6(const vec6& other) = default; // Copy constructor

	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->u = 0;
		this->v = 0;
		this->w = 0;
	}

	inline void set_values(T x, T y, T z, T u, T v, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->u = u;
		this->v = v;
		this->w = w;
	}

	vec6 operator+(const vec6<T>& other) const {
		return vec6(this->x + other.x, this->y + other.y, this->z + other.z, this->u + other.u, this->v + other.v, this->w + other.w);
	}

	vec6 operator+(const T scalar) const {
		return vec6(this->x + scalar, this->y + scalar, this->z + scalar, this->u + scalar, this->v + scalar, this->w + scalar);
	}


	vec6 operator-(const vec6<T>& other) const {
		return vec6(this->x - other.x, this->y - other.y, this->z - other.z, this->u - other.u, this->v - other.v, this->w + other.w);
	}

	vec6 operator-(const T scalar) const {
		return vec6(this->x - scalar, this->y - scalar, this->z - scalar, this->u - scalar, this->v - scalar, this->w - scalar);
	}


	vec6 operator*(const vec6<T>& other) const {
		return vec6(this->x * other.x, this->y * other.y, this->z * other.y, this->u * other.u, this->v * other.v, this->w * other.w);
	}

	vec6 operator*(const T scalar) const {
		return vec6(this->x * scalar, this->y * scalar, this->z * scalar, this->u * scalar, this->v * scalar, this->w * scalar);
	}


	vec6 operator/(const vec6<T>& other) const {
		return vec6(this->x / other.x, this->y / other.y, this->z / other.y, this->u / other.u, this->v / other.v, this->w / other.w);
	}

	vec6 operator/(const T scalar) const {
		return vec6(this->x / scalar, y / scalar, this->z / scalar, this->u / scalar, this->v / scalar, this->w / scalar);
	}


	bool operator==(const vec6<T>& other) const {
		return (this->x == other.x && this->y == other.y && this->z == other.z && this->u == other.u && this->v == other.v && this->w == other.w);
	}

	bool operator!=(const vec6<T>& other) const {
		return !(*this == other);
	}

	vec6<T>& operator=(const vec6<T>& other) {
		if(this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
			u = other.u;
			v = other.v;
			w = other.w;
		}

		return *this;
	}
};

