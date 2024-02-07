#include "../opengl/shader_program.hpp"
#include "../types/color.hpp"
#include "baseshape.hpp"
#include <vector>

class Rectangle : public BaseShape {
	public:
		Rectangle(const float x, const float y, const float width, const float height);
		Rectangle(const float x, const float y, const float width, const float height, const Color& color);
		Rectangle(const float x, const float y, const float width, const float height, const std::vector<float>& colors);

		void make_vertices() const;

		inline void draw_array() const {
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, this->indices.data());
		}
	private:
		std::vector<unsigned int> indices = {
			0, 1, 2,
			0, 2, 3
		};
		const float width;
		const float height;
};
