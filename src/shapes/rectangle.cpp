#include "../../include/shapes/rectangle.hpp"
#include "../../include/utils/calc.hpp"
#include "../../include/window/window.hpp"
#include <vector>

Rectangle::Rectangle(const float x, const float y, const float width, const float height)
	: BaseShape(x, y,
		// INDICES //
		{
			0, 1, 2, // First triangle
			0, 2, 3  // Second triangle
		},

		// COLORS //
		{
			1.0f, 1.0f, 1.0f, // Bottom Right
			1.0f, 1.0f, 1.0f, // Bottom Left
			1.0f, 1.0f, 1.0f,  // Top
			1.0f, 1.0f, 1.0f  // Top
		}),

		width(width), height(height)

	{
		this->make_vertices();
	}

Rectangle::Rectangle(const float x, const float y, const float width, const float height, const Color& color)
	: BaseShape(x, y,
		// INDICES //
		{
			0, 1, 2, // First triangle
			0, 2, 3  // Second triangle
		},

		// COLORS //
		{
			color.r, color.g, color.b, // Top Right
			color.r, color.g, color.b, // Bottom Right
			color.r, color.g, color.b, // Bottom Left
			color.r, color.g, color.b  // Top Left

			// 1.0f, 0.0f, 0.0f,  // Top Right
			// 0.0f, 1.0f, 0.0f,  // Bottom Right
			// 0.0f, 0.0f, 1.0f,  // Bottom Left
			// 1.0f, 1.0f, 0.0f   // Top Left 
		}),

		width(width), height(height)

	{
		this->make_vertices();
	}

void Rectangle::make_vertices() const {
	const float win_width  = static_cast<float>(Window::get_static_width());
	const float win_height = static_cast<float>(Window::get_static_height());

	// Translate Width and Height
	const float trans_width = Calc::translate_size(this->width, win_width);
	const float trans_height = Calc::translate_size(this->height, win_height);

	// Translate X and Y
	const float trans_x = Calc::translate_x(this->x + this->width  / 2.0f, win_width)  - trans_width / 2.0f;
	const float trans_y = Calc::translate_y(this->y + this->height / 2.0f, win_height) - trans_height / 2.0f;

	const std::vector<float> vertices = {
		trans_x,               trans_y,                0.0f, // Top Left
		trans_x + trans_width, trans_y,                0.0f, // Top Right
		trans_x + trans_width, trans_y + trans_height, 0.0f, // Bottom Right
		trans_x,               trans_y + trans_height, 0.0f  // Bottom Left

		// -0.5f, -0.5f, 0.0f,
		//  0.5f, -0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		// -0.5f,  0.5f, 0.0f,

		//  0.5f,  0.5f, 0.0f,
		//  0.5f, -0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f,
		// -0.5f,  0.5f, 0.0f,
	};

	// Colors was defined alredy as position 1, position of vertices keep 1
	this->vbo->store_data(0, 3, vertices);
}
