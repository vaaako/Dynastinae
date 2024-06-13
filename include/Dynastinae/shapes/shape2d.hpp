#pragma once

#include "Dynastinae/shapes/mesh.hpp"

struct Shape2D : Mesh {
	Shape2D(const std::vector<float>& vertices, const std::vector<uint32>& indices);
};
