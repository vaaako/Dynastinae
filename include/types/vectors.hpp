#pragma once

struct Vector2f {
	float x;
	float y;

	Vector2f(const float x, const float y);
};

struct Vector3f : Vector2f {
	float z;

	Vector3f(const float x, const float y, const float z);
};
