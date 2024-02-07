#pragma once

namespace Calc {
	inline float translate_size(const float size, const float window_size) {
		return 2.0f * size / window_size;
	}

	// Calculating NDC
	// Normalize based on OpenGL coords: Range 1.0f to -1.0f
	inline float translate_axis(const float axis, const float window_size) {
		return (2.0f * axis) / window_size;
	}

	// Back 1.0f invert X and normalize (Positive to Negative)
	inline float translate_x(const float x, const float width) {
		return translate_axis(x, width) - 1.0f;
	}

	// Front 1.0f to invert Y and normalize (Negative to Positive)
	inline float translate_y(const float y, const float height) {
		return 1.0f - translate_axis(y, height);
	}
};