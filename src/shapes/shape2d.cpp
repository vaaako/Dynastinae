#include "Dynastinae/shapes/shape2d.hpp"

Shape2D::Shape2D(const std::vector<float>& vertices, const std::vector<uint32>& indices)
	: Mesh(vertices, indices, 2, 2) {}

