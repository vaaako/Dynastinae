#pragma once

#include "../opengl/shader_program.hpp"
#include "../types/color.hpp"
#include "baseshape.hpp"

class Triangle : public BaseShape {
	public:
		Triangle(const float x, const float y, const float size, const Color& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		Triangle(const float x, const float y, const float size, const std::vector<float>& colors);

		void make_vertices() const;

		inline void draw_array() const {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	private:
		const float size;
};
