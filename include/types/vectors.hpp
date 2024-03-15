#pragma once

#include "../utils/math.hpp"

struct Vector2f {
	float x = 0.0f;
	float y = 0.0f;

	Vector2f() = default;
	Vector2f(const float x, const float y);


	Vector2f operator+(const Vector2f& other) {
		return Vector2f(this->x + other.x, this->y + other.y);
	}

	Vector2f operator-(const Vector2f& other) {
		return Vector2f(this->x - other.x, this->y - other.y);
	}

	Vector2f operator*(const Vector2f& other) {
		return Vector2f(this->x * other.x, this->y * other.y);
	}

	Vector2f operator/(const Vector2f& other) {
		return Vector2f(this->x / other.x, this->y / other.y);
	}

	bool operator==(const Vector2f& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y);
	}
};

struct Vector3f : Vector2f {
	float z = 0.0f;

	Vector3f() = default;
	Vector3f(const float x, const float y, const float z);


	Vector3f operator+(const Vector3f& other) {
		return Vector3f(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3f operator-(const Vector3f& other) {
		return Vector3f(this->x - other.x, this->y - other.y, this->z + other.z);
	}

	Vector3f operator*(const Vector3f& other) {
		return Vector3f(this->x * other.x, this->y * other.y, this->z + other.z);
	}

	Vector3f operator/(const Vector3f& other) {
		return Vector3f(this->x / other.x, this->y / other.y, this->z + other.z);
	}

	bool operator==(const Vector3f& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y)
				&& Math::compare_floats(this->z, other.z);
	}
};

struct Vector4f : Vector3f {
	float w = 0.0f;

	Vector4f() = default;
	Vector4f(const float x, const float y, const float z, const float w);


	Vector4f operator+(const Vector4f& other) {
		return Vector4f(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
	}

	Vector4f operator-(const Vector4f& other) {
		return Vector4f(this->x - other.x, this->y - other.y, this->z + other.z, this->w + other.w);
	}

	Vector4f operator*(const Vector4f& other) {
		return Vector4f(this->x * other.x, this->y * other.y, this->z + other.z, this->w + other.w);
	}

	Vector4f operator/(const Vector4f& other) {
		return Vector4f(this->x / other.x, this->y / other.y, this->z + other.z, this->w + other.w);
	}

	bool operator==(const Vector4f& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y)
				&& Math::compare_floats(this->z, other.z)
				&& Math::compare_floats(this->w, other.w);
	}
};


struct Vector5f : Vector4f {
	float h = 0.0f;

	Vector5f() = default;
	Vector5f(const float x, const float y, const float z, const float w, const float h);

	Vector5f operator+(const Vector5f& other) {
		return Vector5f(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	Vector5f operator-(const Vector5f& other) {
		return Vector5f(this->x - other.x, this->y - other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	Vector5f operator*(const Vector5f& other) {
		return Vector5f(this->x * other.x, this->y * other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	Vector5f operator/(const Vector5f& other) {
		return Vector5f(this->x / other.x, this->y / other.y, this->z + other.z, this->w + other.w, this->h + other.h);
	}

	bool operator==(const Vector5f& other) {
		return Math::compare_floats(this->x, other.x)
				&& Math::compare_floats(this->y, other.y)
				&& Math::compare_floats(this->z, other.z)
				&& Math::compare_floats(this->w, other.w)
				&& Math::compare_floats(this->h, other.h);
	}
};
