#pragma once

#include "Dynastinae/shapes/mesh.hpp"
#include "Dynastinae/scenes/camera.hpp"
#include "Dynastinae/scenes/scene.hpp"
#include "Dynastinae/utils/file.hpp"
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Scene3D : public Scene {
	public:
		Scene3D(Camera& camera);

		inline void draw_shape(const Mesh& mesh, const DrawMode drawmode = DrawMode::FILL, const uint32 drawtype = GL_TRIANGLE_FAN) const {
			mesh.draw3d(this->camera, (mesh.get_texture() != nullptr) ? *this->shader_texture : *this->shader, drawmode, drawtype);
		}

		inline const Camera& get_camera() const {
			return this->camera;
		}

		inline void update_viewport(const Window& window) {
			camera.update_viewport(window.get_width(), window.get_height());
		}

		inline void update_viewport(const uint32 width, const uint32 height) {
			camera.update_viewport(width, height);
		}


		// NOTE -- template methods need to be referenced on header file

		// Variadic template function to accept multiple Mesh objects
		template <typename... Meshes>
		void draw_shapes(const Meshes&... meshes) const {
			// Store the meshes in a vector
			std::vector<const Mesh*> buffer  = { &meshes... };

			// Draw each
			for(const Mesh* mesh : buffer) {
				mesh->draw3d(
					this->camera,
					(mesh->get_texture() != nullptr) ? *this->shader_texture : *this->shader,
					DrawMode::FILL
				);
			}
		}

		template <typename... Meshes>
		void draw_shapes(const DrawMode drawmode, const Meshes&... meshes) const {
			// Store the meshes in a vector
			std::vector<const Mesh*> buffer  = { &meshes... };

			// Draw each
			for(const Mesh* mesh : buffer) {
				mesh->draw3d(
					this->camera,
					(mesh->get_texture() != nullptr) ? *this->shader_texture : *this->shader,
					drawmode
				);
			}
		}
	private:
		std::vector<Mesh> shapes;
		Camera& camera;

		// Shaders
		const char* vertex_shader = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/3d/vertex.glsl");
		const char* fragment_shader = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/3d/fragment.glsl");

		const char* vertex_shader_texture = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/3d/vertex_texture.glsl");
		const char* fragment_shader_texture = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/3d/fragment_texture.glsl");
};
