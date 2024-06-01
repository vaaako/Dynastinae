#pragma once

#include <cmath>

namespace MathHelper {
	inline bool compare_floats(const float a, const float b, const float tolerance = 0.00001f) {
		return std::abs(a - b) < tolerance;
	}
}
