#pragma once

#include "Dynastinae/types/font.hpp"
#include "Dynastinae/scenes/scene.hpp"
#include "Dynastinae/utils/file.hpp"

class Scene2D : public Scene {
	public:
		Scene2D(const Window& window);
		Scene2D(const uint32 width, const uint32 height);

		inline void draw_shape(const Mesh& mesh, const DrawMode drawmode = DrawMode::FILL, const uint32 drawtype = GL_TRIANGLE_FAN) {
			mesh.draw2d((mesh.get_texture() != nullptr) ? *this->shader_texture : *this->shader, drawmode, drawtype);
		}

		// Variadic template function to accept multiple Mesh objects
		template <typename... Meshes>
		inline void draw_shapes(const Meshes&... meshes) const {
			// Store the meshes in a vector
			std::vector<const Mesh*> buffer  = { &meshes... };

			// Draw each
			for(const Mesh* mesh : buffer) {
				mesh->draw2d(
					(mesh->get_texture() != nullptr) ? *this->shader_texture : *this->shader,
					DrawMode::FILL
				);
			}
		}


		inline void draw_font(Font& font) const {
			font.draw2d(*this->shader_texture, DrawMode::FILL, GL_TRIANGLE_FAN);
		}

		// NOTE -- not sure if i have to change glViewport too
		inline void update_viewport(const Window& window) {
			this->update_viewport(window.get_width(), window.get_height());
		}
		void update_viewport(const uint32 width, const uint32 height);

	private:
		// Shaders
		const char* vertex_shader = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/2d/vertex.glsl");
		const char* fragment_shader = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/2d/fragment.glsl");

		const char* vertex_shader_texture = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/2d/vertex_texture.glsl");
		const char* fragment_shader_texture = FileHelper::get_file_content(SOURCE_DIR + "/../opengl/shaders/2d/fragment_texture.glsl");
};

