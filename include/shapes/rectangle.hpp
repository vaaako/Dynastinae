#include "../opengl/shader_program.hpp"
#include "../types/color.hpp"
#include "baseshape.hpp"
#include <vector>

class Rectangle : public BaseShape {
	public:
		// Color
		Rectangle(const float x, const float y, const float width, const float height, const Color& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		Rectangle(const float x, const float y, const float width, const float height, const std::vector<float>& colors);

		// Texture
		Rectangle(const float x, const float y, const float width, const float height, const Texture& texture);

		void make_vertices() const;

		inline void draw_array() const override {
			// glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, this->indices.data());
 			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	private:
		const float width;
		const float height;
};
