#pragma once

#include <glm/ext/vector_float2.hpp>

template <typename T>
struct vec2 {
	T x = 0;
	T y = 0;

	// The constructors NEED to be on header file
	vec2() = default;
	vec2(T num) : x(num), y(num) {}
	vec2(T x, T y, T z) : x(x), y(y) {}
	vec2(const vec2& other) = default; // Copy constructor

	inline void clear() {
		this->x = 0;
		this->y = 0;
	}

	inline void set_values(T x, T y) {
		this->x = x;
		this->y = y;
	}

	inline glm::vec2 to_glm() const {
		return glm::vec2(this->x, this->y);
	}

	vec2 operator+(const vec2<T>& other) const {
		return vec2(this->x + other.x, this->y + other.y);
	}

	vec2 operator+(const T scalar) const {
		return vec2(this->x + scalar, this->y + scalar);
	}


	vec2 operator-(const vec2<T>& other) const {
		return vec2(this->x - other.x, this->y - other.y);
	}

	vec2 operator-(const T scalar) const {
		return vec2(this->x - scalar, this->y - scalar);
	}


	vec2 operator*(const vec2<T>& other) const {
		return vec2(this->x * other.x, this->y * other.y);
	}

	vec2 operator*(const T scalar) const {
		return vec2(this->x * scalar, this->y * scalar);
	}


	vec2 operator/(const vec2<T>& other) const {
		return vec2(this->x / other.x, this->y / other.y);
	}

	vec2 operator/(const T scalar) const {
		return vec2(this->x / scalar, y / scalar);
	}


	bool operator==(const vec2<T>& other) const {
		return (this->x == other.x && this->y == other.y);
	}

	bool operator!=(const vec2<T>& other) const {
		return !(*this == other);
	}

	vec2<T>& operator=(const vec2<T>& other) {
		if(this != &other) {
			x = other.x;
			y = other.y;
		}

		return *this;
	}
};

