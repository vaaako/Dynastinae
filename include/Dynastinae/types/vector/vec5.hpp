#pragma once

template <typename T>
struct vec5 {
	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;
	T h = 0;

	vec5() = default;
	vec5(T num) : x(num), y(num), z(num), w(num), h(num) {}
	vec5(T x, T y, T z, T w, T h) : x(x), y(y), z(z), w(w), h(h) {}
	vec5(const vec5& other) = default; // Copy constructor

	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
		this->h = 0;
	}

	inline void set_values(T x, T y, T z, T w, T h) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		this->h = h;
	}

	vec5 operator+(const vec5<T>& other) const {
		return vec5(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	vec5 operator+(const T scalar) const {
		return vec5(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar, this->h + scalar);
	}


	vec5 operator-(const vec5<T>& other) const {
		return vec5(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w, this->h - other.h);
	}

	vec5 operator-(const T scalar) const {
		return vec5(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar, this->h - scalar);
	}


	vec5 operator*(const vec5<T>& other) const {
		return vec5(this->x * other.x, this->y * other.y, this->z * other.y, this->w * other.w, this->h * other.h);
	}

	vec5 operator*(const T scalar) const {
		return vec5(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar, this->h * scalar);
	}


	vec5 operator/(const vec5<T>& other) const {
		return vec5(this->x / other.x, this->y / other.y, this->z / other.y, this->w / other.w, this->h / other.h);
	}

	vec5 operator/(const T scalar) const {
		return vec5(this->x / scalar, y / scalar, this->z / scalar, this->w / scalar, this->h / scalar);
	}


	bool operator==(const vec5<T>& other) const {
		return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w && this->h == other.h);
	}

	bool operator!=(const vec5<T>& other) const {
		return !(*this == other);
	}

	vec5<T>& operator=(const vec5<T>& other) {
		if(this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
			h = other.h;
		}

		return *this;
	}

	vec5<T>& operator=(const T other) {
		x = other;
		y = other;
		z = other;
		w = other;
		h = other;

		return *this;
	}
};

