#pragma once

#include <glm/ext/vector_float3.hpp>

template <typename T>
struct vec3 {
	T x = 0;
	T y = 0;
	T z = 0;

	vec3() = default;
	vec3(T num) : x(num), y(num), z(num) {}
	vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	vec3(const vec3& other) = default; // Copy constructor

	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	inline void set_values(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline glm::vec3 to_glm() const {
		return glm::vec3(this->x, this->y, this->z);
	}

	vec3 operator+(const vec3<T>& other) const {
		return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	vec3 operator+(const T scalar) const {
		return vec3(this->x + scalar, this->y + scalar, this->z + scalar);
	}


	vec3 operator-(const vec3<T>& other) const {
		return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	vec3 operator-(const T scalar) const {
		return vec3(this->x - scalar, this->y - scalar, this->z - scalar);
	}


	vec3 operator*(const vec3<T>& other) const {
		return vec3(this->x * other.x, this->y * other.y, this->z * other.y);
	}

	vec3 operator*(const T scalar) const {
		return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
	}


	vec3 operator/(const vec3<T>& other) const {
		return vec3(this->x / other.x, this->y / other.y, this->z / other.y);
	}

	vec3 operator/(const T scalar) const {
		return vec3(this->x / scalar, y / scalar, this->z / scalar);
	}


	bool operator==(const vec3<T>& other) const {
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}

	bool operator!=(const vec3<T>& other) const {
		return !(*this == other);
	}

	vec3<T>& operator=(const vec3<T>& other) {
		if(this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}

		return *this;
	}

	vec3<T>& operator=(const T other) {
		x = other;
		y = other;
		z = other;

		return *this;
	}
};

