#pragma once

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

/*
 * I am just using union here so when making Mesh for 2D Shape, I can use "position2d" and "vec2"
 * so it is a bit less confusing.
 * Howhever, since union members share the same memory space, when using on OpenGL
 * is used as a vec3 anyway, because OpenGL read the data in memory, not the data itself.
 * So the only use for this union is the label, because even in the shader I had to change aPos to vec3
 */

struct Vertex {
	union {
		glm::vec2 position;
		glm::vec3 position2d;
	};

	glm::vec2 texuv;
};

