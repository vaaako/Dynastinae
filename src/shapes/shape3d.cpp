#include "Dynastinae/shapes/shape3d.hpp"

Shape3D::Shape3D(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
	: Mesh(vertices, indices) {}
