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
			delete this->shader;
			delete this->shader_texture;
		}

		// This will be inited on respective renders (Renderer2D and Camera)
		const ShaderProgram* shader = nullptr;
		const ShaderProgram* shader_texture = nullptr;

		virtual inline void update_viewport(const Window& window) = 0;
		virtual inline void update_viewport(const uint32 width, const uint32 height) = 0;

	protected:
		uint32 width;
		uint32 height;
};
