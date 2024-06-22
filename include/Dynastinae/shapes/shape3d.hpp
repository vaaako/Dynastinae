#pragma once

#include "Dynastinae/shapes/mesh.hpp"

struct Shape3D : public Mesh {
	Shape3D(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices);
};
