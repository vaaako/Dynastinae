#include "../../include/shapes/triangle.hpp"
#include "../../include/window/window.hpp"
#include "../../include/utils/calc.hpp"

Triangle::Triangle(const float x, const float y, const float size, const Color& color)
	: BaseShape(x, y, { 0, 1, 2 },
		{
			color.r, color.g, color.b, color.a, // Bottom Right
			color.r, color.g, color.b, color.a, // Bottom Left
			color.r, color.g, color.b, color.a  // Top
		}
	), size(size)

	{
		this->make_vertices();
	}


Triangle::Triangle(const float x, const float y, const float size, const std::vector<float>& colors)
	: BaseShape(x, y, { 0, 1, 2 }, colors), size(size)

	{

		this->make_vertices();
	}



void Triangle::make_vertices() const {
	const float width  = static_cast<float>(Window::get_static_width());
	const float height = static_cast<float>(Window::get_static_height());

	// Translate Width and Height
	const float trans_size = Calc::translate_size(this->size, width);

	// Translate X and Y
	const float trans_x = Calc::translate_x(this->x + this->size  / 2.0f, width)  - trans_size / 2.0f;
	const float trans_y = Calc::translate_y(this->y + this->size  / 2.0f, height) - trans_size / 2.0f;

	// Dividing by 2: Creates an equilateral 
	const std::vector<float> vertices = {
		trans_x,                     trans_y,              0.0f, // Top Left
		trans_x + trans_size,        trans_y,              0.0f, // Top Right
		trans_x + trans_size / 2.0f, trans_y + trans_size, 0.0f  // Bottom Middle
	};

	// Colors was defined alredy as position 1, position of vertices keep 1
	this->vbo->store_data(vertices, 0, 3);
}


// -0.5f, -0.5f, 0.0f,
//  0.5f, -0.5f, 0.0f,
//  0.0f,  0.5f, 0.0f
