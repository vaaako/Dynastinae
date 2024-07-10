#pragma once

#include <cmath>

namespace MathHelper {
	inline bool compare_floats(const float a, const float b, const float tolerance = 0.00001f) {
		return std::abs(a - b) < tolerance;
	}

	// Returns true if v1 can be considered equal to v2
	inline bool is_near(const float v1, const float v2) {
		return std::fabs(v1 - v2) < 0.01f;
	}
}
