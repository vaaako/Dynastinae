#pragma once

#include <glm/ext/vector_float4.hpp>

template <typename T>
struct vec4 {
	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;

	vec4() = default;
	vec4(T num) : x(num), y(num), z(num), w(num) {}
	vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	vec4(const vec4& other) = default; // Copy constructor

	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	inline void set_values(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline glm::vec4 to_glm() const {
		return glm::vec4(this->x, this->y, this->z, this->w);
	}

	vec4 operator+(const vec4<T>& other) const {
		return vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
	}

	vec4 operator+(const T scalar) const {
		return vec4(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
	}


	vec4 operator-(const vec4<T>& other) const {
		return vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
	}

	vec4 operator-(const T scalar) const {
		return vec4(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
	}


	vec4 operator*(const vec4<T>& other) const {
		return vec4(this->x * other.x, this->y * other.y, this->z * other.y, this->w * other.w);
	}

	vec4 operator*(const T scalar) const {
		return vec4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}


	vec4 operator/(const vec4<T>& other) const {
		return vec4(this->x / other.x, this->y / other.y, this->z / other.y, this->w / other.w);
	}

	vec4 operator/(const T scalar) const {
		return vec4(this->x / scalar, y / scalar, this->z / scalar, this->w / scalar);
	}


	bool operator==(const vec4<T>& other) const {
		return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
	}

	bool operator!=(const vec4<T>& other) const {
		return !(*this == other);
	}

	vec4<T>& operator=(const vec4<T>& other) {
		if(this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		return *this;
	}

	vec4<T>& operator=(const T other) {
		x = other;
		y = other;
		z = other;
		w = other;

		return *this;
	}
};

