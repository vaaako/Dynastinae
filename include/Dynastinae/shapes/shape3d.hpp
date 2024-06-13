#pragma once

#include "Dynastinae/shapes/mesh.hpp"

struct Shape3D : Mesh {
	Shape3D(const std::vector<float>& vertices, const std::vector<uint32>& indices);
};
