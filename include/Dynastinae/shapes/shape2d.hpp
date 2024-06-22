#pragma once

#include "Dynastinae/shapes/mesh.hpp"

struct Shape2D : public Mesh {
	Shape2D(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices);
};
