#include "Dynastinae/shapes/shape3d.hpp"

Shape3D::Shape3D(const std::vector<float>& vertices, const std::vector<uint32>& indices)
	: Mesh(vertices, indices, 3, 2) {}
