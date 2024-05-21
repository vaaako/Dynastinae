#pragma once

#include <glm/ext.hpp>
#include "../utils/math.hpp"

template <typename T>
struct Vector2 {
	T x = 0.0f;
	T y = 0.0f;

	Vector2() = default;
	Vector2(const T x, const T y);

	inline void clear() {
		this->x = 0;
		this->y = 0;
	}

	inline void set_values(const T x, const T y) {
		this->x = x;
		this->y = y;
	}
	
	glm::vec2 to_glm() const {
		return glm::vec2(this->x, this->y);
	}

	Vector2 operator+(const Vector2& other) {
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 operator-(const Vector2& other) {
		return Vector2(this->x - other.x, this->y - other.y);
	}

	Vector2 operator*(const Vector2& other) {
		return Vector2(this->x * other.x, this->y * other.y);
	}

	Vector2 operator/(const Vector2& other) {
		return Vector2(this->x / other.x, this->y / other.y);
	}

	bool operator==(const Vector2& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y);
	}
};

struct Vector3 : Vector2 {
	float z = 0.0f;

	Vector3() = default;
	Vector3(const float x, const float y, const float z);


	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	inline void set_values(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	glm::vec3 to_glm() const {
		return glm::vec3(this->x, this->y, this->z);
	}

	Vector3 operator+(const Vector3& other) {
		return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3 operator-(const Vector3& other) {
		return Vector3(this->x - other.x, this->y - other.y, this->z + other.z);
	}

	Vector3 operator*(const Vector3& other) {
		return Vector3(this->x * other.x, this->y * other.y, this->z + other.z);
	}

	Vector3 operator/(const Vector3& other) {
		return Vector3(this->x / other.x, this->y / other.y, this->z + other.z);
	}

	bool operator==(const Vector3& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y)
				&& Math::compare_floats(this->z, other.z);
	}
};

struct Vector4 : Vector3 {
	float w = 0.0f;

	Vector4() = default;
	Vector4(const float x, const float y, const float z, const float w);

	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	inline void set_values(const float x, const float y, const float z, const float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	glm::vec4 to_glm() const {
		return glm::vec4(this->x, this->y, this->z, this->w);
	}

	Vector4 operator+(const Vector4& other) {
		return Vector4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
	}

	Vector4 operator-(const Vector4& other) {
		return Vector4(this->x - other.x, this->y - other.y, this->z + other.z, this->w + other.w);
	}

	Vector4 operator*(const Vector4& other) {
		return Vector4(this->x * other.x, this->y * other.y, this->z + other.z, this->w + other.w);
	}

	Vector4 operator/(const Vector4& other) {
		return Vector4(this->x / other.x, this->y / other.y, this->z + other.z, this->w + other.w);
	}

	bool operator==(const Vector4& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y)
				&& Math::compare_floats(this->z, other.z)
				&& Math::compare_floats(this->w, other.w);
	}
};


struct Vector5 : Vector4 {
	float h = 0.0f;

	Vector5() = default;
	Vector5(const float x, const float y, const float z, const float w, const float h);


	inline void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
		this->h = 0;
	}

	inline void set_values(const float x, const float y, const float z, const float w, const float h) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		this->h = h;
	}

	Vector5 operator+(const Vector5& other) {
		return Vector5(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	Vector5 operator-(const Vector5& other) {
		return Vector5(this->x - other.x, this->y - other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	Vector5 operator*(const Vector5& other) {
		return Vector5(this->x * other.x, this->y * other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	Vector5 operator/(const Vector5& other) {
		return Vector5(this->x / other.x, this->y / other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	bool operator==(const Vector5& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y)
				&& Math::compare_floats(this->z, other.z)
				&& Math::compare_floats(this->w, other.w)
				&& Math::compare_floats(this->h, other.h);
	}
};



/**
 * INTEGER */

struct Vector2i {
	int x = 0.0f;
	int y = 0.0f;

	Vector2i() = default;
	Vector2i(const int x, const int y);

	inline void clear() {
		this->x = 0;
		this->y = 0;
	}

	inline void set_values(int x, const int y) {
		this->x = x;
		this->y = y;
	}

	glm::vec2 to_glm() const {
		return glm::vec2(this->x, this->y);
	}

	Vector2i operator+(const Vector2i& other) {
		return Vector2i(this->x + other.x, this->y + other.y);
	}

	Vector2i operator-(const Vector2i& other) {
		return Vector2i(this->x - other.x, this->y - other.y);
	}

	Vector2i operator*(const Vector2i& other) {
		return Vector2i(this->x * other.x, this->y * other.y);
	}

	Vector2i operator/(const Vector2i& other) {
		return Vector2i(this->x / other.x, this->y / other.y);
	}

	bool operator==(const Vector2i& other) {
		return this->x == other.x && this->y == other.y;
	}
};
