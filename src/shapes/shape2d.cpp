#include "Dynastinae/shapes/shape2d.hpp"

Shape2D::Shape2D(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
	: Mesh(vertices, indices, 3, 2) {}

