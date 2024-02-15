#include "../types/color.hpp"
#include "shape2d.hpp"

class Rectangle : public Shape2D {
	public:
		// Color
		Rectangle(const float x, const float y, const float width, const float height, const Color& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		Rectangle(const float x, const float y, const float width, const float height, const std::vector<float>& colors);

		// Texture
		Rectangle(const float x, const float y, const float width, const float height, const Texture& texture);

		void make_vertices() const;
	private:
		const float width;
		const float height;
};
