#pragma once

#include "Dynastinae/window/window.hpp"
#include "Dynastinae/opengl/shader_program.hpp"

enum class DrawMode {
	LINE = 6913,
	FILL = 6914
};

class Scene {
	public:
		Scene(const Window& window);
		Scene(const uint32 width, const uint32 height);
		~Scene() {
			// delete this->shader;
			// delete this->shader_texture;
		}

		inline const ShaderProgram& get_shader() const {
			return *this->shader;
		}

		inline const ShaderProgram& get_shader_texture() const {
			return *this->shader_texture;
		}

		virtual inline void update_viewport(const Window& window) = 0;
		virtual inline void update_viewport(const uint32 width, const uint32 height) = 0;

	protected:
		// Pointers to avoid forced init on this constructor
		const ShaderProgram* shader = nullptr;
		const ShaderProgram* shader_texture = nullptr;

		uint32 width;
		uint32 height;
};

