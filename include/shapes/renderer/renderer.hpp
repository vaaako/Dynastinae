#pragma once

#include "../../opengl/shader_program.hpp"
#include "../../types/color.hpp"
#include "../../types/vectors.hpp"
#include "../shape2d.hpp"
#include "../shape3d.hpp"
#include <memory>

enum class DrawMode {
	LINE = 6913,
	FILL = 6914
};

class Renderer {
	public:
		Renderer() = default;

	private:
		// Just defaults for draw_3d
		const float fov = 45.0f;
		const float near_plane = 0.1f;
		const float far_plane = 100.0f;

	protected:
		std::unique_ptr<const ShaderProgram> shader = nullptr;
		std::unique_ptr<const ShaderProgram> shader_texture = nullptr;

		void draw_2d(const Shape2D& shape, const ShaderProgram& shader, const GLenum draw_type,
				const Texture* texture, const Vector2f pos, Vector2f size, const Color& color = { 255 },
				const float rotate = 0.0f, const DrawMode draw_mode = DrawMode::FILL) const;

		void draw_3d(const Shape3D& shape, const ShaderProgram& shader,
			const Texture* texture, const Vector3f pos, const Color& color = { 255 },
			const float rotate = 0.0f, const Vector3f axis = { 0.0f, 0.0f, 0.0f }, const DrawMode draw_mode = DrawMode::FILL) const;
};

