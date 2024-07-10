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



// Avoid foward declaration
class Scene2D;
class Scene3D;

// TODO -- Take color in constructor (for complex colors)

class Mesh {
	public:
		// Decide what to do later
		Mesh();
		// Custom shape
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices);
		// Load obj file
		Mesh(const std::string& path);
		~Mesh() {
			// No need to delete texture, since is actually a "reference" to another texture
			delete this->vao;
		}


		// TODO -- remove from mesh and put on shape2d or shape3d?
		void draw2d(const ShaderProgram& shader, const DrawMode drawmode = DrawMode::FILL, const uint32 drawtype = GL_TRIANGLES) const;
		void draw3d(const Camera& camera, const ShaderProgram& shader, const DrawMode drawmode = DrawMode::FILL, const uint32 drawtype = GL_TRIANGLES) const;

		std::vector<Vertex> load_obj(const std::string& path, std::vector<uint32>& out_indices, bool& has_texuv);



		inline const Texture* get_texture() const {
			return this->texture;
		}


		inline Mesh& set_angle(const float angle) {
			this->angle = angle;
			return *this;
		}

		inline Mesh& set_axis(const vec3<int8> axis) {
			this->axis = axis;
			return *this;
		}

		inline Mesh& set_color(const Color& color) {
			this->color = color;
			return *this;
		}


		inline Mesh& set_size(const float size) {
			this->size.set_values(size, size, size);
			return *this;
		}

		inline Mesh& set_size(const vec2<float> size) {
			this->size.set_values(size.x, size.y, 0.0f);
			return *this;
		}

		inline Mesh& set_size(const vec3<float> size) {
			this->size = size;
			return *this;
		}


		inline Mesh& set_scale(const float scale) {
			this->size = this->size * scale;
			return *this;
		}

		inline Mesh& set_scale(const vec3<float> scale) {
			this->size = this->size * scale;
			return *this;
		}



		inline Mesh& set_position(const vec2<float> position) {
			this->position.set_values(position.x, position.y, 0.0f);
			return *this;
		}

		inline Mesh& set_position(const vec3<float> position) {
			this->position = position;
			return *this;
		}

		inline Mesh& set_texture(Texture* texture) {
			if(!has_texuv) {
				LOG_INFO("This mesh does not support texture");
				return *this;
			}

			this->texture = texture;
			return *this;
		}

	private:
		Texture* texture = nullptr; // Pointer because might be nullptr
		Color color = 255;
		vec3<float> position;
		vec3<int8> axis = { 0, 1, 0 }; // If is all zero the mesh isn't rendered, this won't affect the Mesh if angle is zero
		vec3<float> size = { 1.0f, 1.0f, 1.0f };
		float angle = 0;
		bool has_texuv = true;

		// Safe free memory
		VAO* vao = new VAO();
		GLsizei indices_size; // Pre calculated indices size
		GLsizei vertices_size = 0; // Used for models only (currently)

		// All below are inline because it should be in draw methods
		inline void draw_start(const ShaderProgram& shader, const DrawMode drawmode) const {
			glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(drawmode));
			shader.use();
		}

		inline void draw_end(const ShaderProgram& shader, const uint32 drawtype) const {
			shader.set_vector4f("shapeColor", vec4(this->color.r / 255.0f, this->color.g / 255.0f, this->color.b / 255.0f, this->color.a / 255.0f));

			// TODO -- How to avoid this if-check?
			if(this->texture != nullptr) {
				this->texture->bind();
			}

			this->vao->bind();

			glDrawElements(drawtype, this->indices_size, GL_UNSIGNED_INT, (void*)0);
		}
};
