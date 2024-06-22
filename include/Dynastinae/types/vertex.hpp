#pragma once

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

/* NOTE
 * I am just using union here so when making Mesh for 2D Shape, I can use "position2d" and "vec2"
 * so it is a bit less confusing.
 *  
 * However, since union members share the same memory space, when using on OpenGL
 * is used as a vec3 anyway, because OpenGL read the data in memory, not the data itself.
 * This was leading to the shape2D not be drawing correctly
 * (since it ignored the 2D offset and used the 3D offset, using texuv as vertice)
 *  
 * To solve this, I am using shape2d as 3D anyway, and just using XY and ignoring Z
 * even in the shader I had to change aPos to vec3
 *  
 * So the only use for this union is the label and use vec2
 * (even though is later read as vec3)
 */

struct Vertex {
	union {
		glm::vec3 position;
		glm::vec2 position2d;
	};

	glm::vec2 texuv;
};

