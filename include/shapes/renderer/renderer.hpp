#pragma once

#include "../../window/window.hpp"
#include "../../opengl/shader_program.hpp"

enum class DrawMode {
	LINE = 6913,
	FILL = 6914
};

class Renderer {
	public:
		Renderer(const Window& window);
		Renderer(const unsigned int width, const unsigned int height);
		~Renderer() {
			delete this->shader;
			delete this->shader_texture;
		}

		// This will be inited on respective renders (Renderer2D and Camera)
		const ShaderProgram* shader = nullptr;
		const ShaderProgram* shader_texture = nullptr;

		virtual inline void update_viewport(const Window& window) = 0;
		virtual inline void update_viewport(const unsigned int width, const unsigned int height) = 0;
	protected:
		// TODO -- Store as float
		unsigned int width;
		unsigned int height;
};

