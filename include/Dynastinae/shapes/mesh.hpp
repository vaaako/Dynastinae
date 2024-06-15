#pragma once

#include <vector>
#include "Dynastinae/opengl/shader_program.hpp"
#include "Dynastinae/opengl/vao.hpp"
#include "Dynastinae/scenes/camera.hpp"
#include "Dynastinae/scenes/scene.hpp"
#include "Dynastinae/types.hpp"
#include "Dynastinae/types/color.hpp"
#include "Dynastinae/types/texture.hpp"
#include "Dynastinae/types/vector/vec3.hpp"
#include "Dynastinae/types/vertex.hpp"


/*
 * https://github.com/VictorGordan/opengl-tutorials/tree/main/YoutubeOpenGL%2012%20-%20Mesh%20Class
 *
 * TODO
 * - Only VAO object
 * - [X] Vertex struct
 *   + [X] three vec3: position, texuv and color (maybe idk)
 * - [ ] VBO constructor instead of store_data methods (?)
 *   + [ ] Accept vector of Vertex as param
 * - [ ] Review necessary and uncessary methods in VBO and EBO
 * - [ ] Draw method in Mesh struct
 * - [ ] Instead of a a struct for each shape, construct on each scene
 *   + [ ]i or not? to avoid putting all the long vertices and indices vectors on these classes
 */


// LATER
// TODO -- Rotate and Position (maybe) methods (maybe will need VBO back)
// TODO -- Take color in constructor
// TODO -- Change Texture to reference, if possible (remember to change on font.hpp)

struct Mesh {
	// I don't think I need to store this two
	// const std::vector<Vertex> vertices;
	// const std::vector<uint32> indices;
	const uint64 indices_size; // Pre calculated indices size

	// Safe free memory
	VAO* vao = new VAO();

	vec3<float> position;
	vec3<float> size;
	float rotate_speed = 0;
	Color color = 255;

	Texture* texture = nullptr; // Pointer because might be nullptr


	// Position and Texture dimension for building VBO
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices, const uint8 pos_dim, const uint8 tex_dim);
	Mesh(const std::vector<float>& vertices, const std::vector<uint32>& indices, const uint8 pos_dim, const uint8 tex_dim);
	~Mesh() {
		// No need to delete texture, since is actually a "reference" to another texture
		delete this->vao;
	}

	inline void set_texture(Texture* texture) {
		if(this->texture) {
			delete this->texture;
		}

		this->texture = texture;
	}

	void draw2d(const ShaderProgram& shader, const DrawMode draw_mode, const uint32 draw_type = GL_TRIANGLES) const;
	void draw3d(const Camera& camera, const ShaderProgram& shader, const DrawMode draw_mode, const uint32 draw_type = GL_TRIANGLES) const;

	private:
		inline void draw_start(const ShaderProgram& shader, const DrawMode draw_mode) const {
			glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(draw_mode));
			shader.use();
		}

		inline void draw_end(const ShaderProgram& shader, const uint32 draw_type) const {
			shader.set_vector4f("shapeColor", vec4(this->color.r / 255.0f, this->color.g / 255.0f, this->color.b / 255.0f, color.a / 255.0f));

			// TODO -- Think on a way of avoiding "if"
			//      -- Think on something to add on shader
			if(this->texture != nullptr) {
				this->texture->bind();
			}

			this->vao->bind();
			glDrawElements(draw_type, static_cast<int>(this->indices_size), GL_UNSIGNED_INT, (void*)0);
		}
};
