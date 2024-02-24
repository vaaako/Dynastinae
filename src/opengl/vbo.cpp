#include "../../include/opengl/vbo.hpp"
#include <cstdint>

#define INT2VOID(v) (void*)(uintptr_t)(v)

VBO::VBO() {}

void VBO::store_single_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimensions) {
	this->vbo_size += data.size() * sizeof(float);
	
	glGenBuffers(1, &this->id); // BUG -- Do i need every time?? No?? So why don't work when i keep this on constructor???
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	glBufferData(GL_ARRAY_BUFFER, this->vbo_size, data.data(), GL_STATIC_DRAW);

	// Configure the Vertex Attribute so OpenGl knows how to read the VBO
	glVertexAttribPointer(position, dimensions, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(position);     // Enabling Vertex Position to draw
	glBindBuffer(GL_ARRAY_BUFFER, this->id); // Unbind VBO
}

// TODO -- More describle names

// One data
// shape2d_texture
void VBO::store_data(const std::vector<float>& data, const unsigned int field1_dimensions, const unsigned int field2_dimensions) {
	this->vbo_size += data.size() * sizeof(float);
	const int total_dimension = field1_dimensions + field2_dimensions;


	// Create and bind VBO
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	// Allocate Memory
	glBufferData(GL_ARRAY_BUFFER, this->vbo_size, data.data(), GL_STATIC_DRAW);

	// Seet Data Vertex Attribute
	glVertexAttribPointer(0, field1_dimensions, GL_FLOAT, GL_FALSE, total_dimension * sizeof(float), (void*)0); // position attribute
	glEnableVertexAttribArray(0);
	// Texture coordinate
	glVertexAttribPointer(1, field2_dimensions, GL_FLOAT, GL_FALSE, total_dimension * sizeof(float), (void*)(field2_dimensions * sizeof(float))); // texture coords
	glEnableVertexAttribArray(1);

	// Allocate Memory
	glBindBuffer(GL_ARRAY_BUFFER, this->id); // Unbind VBO
}

// shape2d_texture
void VBO::store_data(const std::vector<float>& data, const std::vector<float>& data2, const unsigned int field1_dimensions, const unsigned int field2_dimensions) {
	// Make one vector
	std::vector<float> intervelated_data = data;
	intervelated_data.insert(intervelated_data.end(), data2.begin(), data2.end()); // Combine datas

	// Local vars
	const int total_dimensions = field1_dimensions + field2_dimensions;
	const long unsigned int data_size  = data.size() * sizeof(float);
	this->vbo_size += intervelated_data.size() * sizeof(float);

	// Create and bind VBO
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	// Allocate Memory
	glBufferData(GL_ARRAY_BUFFER, this->vbo_size, intervelated_data.data(), GL_STATIC_DRAW);

	// Seet Data Vertex Attribute
	glVertexAttribPointer(0, field1_dimensions, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), (void*)0); // position attribute
	glEnableVertexAttribArray(0);
	// Texture coordinate
	// Offset: Vertex dimension
	glVertexAttribPointer(1, field2_dimensions, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), (void*)(field1_dimensions * sizeof(float))); // texture coords
	glEnableVertexAttribArray(1);


	// Set Data2 Vertex Attribute
	// Offset: Data1 Vertices + Texture Coordinates
	glVertexAttribPointer(2, field1_dimensions, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), (void*)(data_size)); // position attribute
	glEnableVertexAttribArray(2);
	// Texture coordinate
	// Offset: Data1 Vertices + Texture Coordinates + Data2 Vertex dimensions
	glVertexAttribPointer(3, field2_dimensions, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), (void*)(data_size + field1_dimensions)); // position attribute
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, this->id); // Unbind VBO
}




/*
void VBO::store_data(const std::vector<float>& data, const unsigned int vertex_start, const std::vector<unsigned int> dimensions) {
	this->vbo_size += data.size() * sizeof(float);

	// Create and bind VBO
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	// Allocate Memory
	glBufferData(GL_ARRAY_BUFFER, this->vbo_size, nullptr, GL_STATIC_DRAW);


	// WARNING -- Not tested, must be wrong :/
	auto total_dimensions = std::accumulate(dimensions.begin(), dimensions.end(), 0);
	const unsigned int last_dimension = 0;
	for(int i = 0; i < dimensions.size(); i++) {
		const unsigned int dim = dimensions.at(i);
		const unsigned int last_dimension = dim;

		// Seet Data Vertex Attribute
		glVertexAttribPointer(i, dim, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), INT2VOID(last_dimension * sizeof(float)));
		glEnableVertexAttribArray(i);
	}

}
*/


/*

void VBO::add_colors(const std::vector<float>& colors1, const std::vector<float>& colors2, const unsigned int color_dimensions) {
    // Calculate the size of color data
    const long unsigned int color1_size = colors1.size() * sizeof(float);
    const long unsigned int color2_size = colors2.size() * sizeof(float);
    
    // Calculate the total size including color data
    const long unsigned int total_size = this->vbo_size + color1_size + color2_size;

    // Reallocate memory
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, total_size, nullptr, GL_STATIC_DRAW);

    // Upload color data
    glBufferSubData(GL_ARRAY_BUFFER, this->vbo_size, color1_size, colors1.data());
    glBufferSubData(GL_ARRAY_BUFFER, this->vbo_size + color1_size, color2_size, colors2.data());

    // Update vertex attribute pointers for colors
    glVertexAttribPointer(4, color_dimensions, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), (void*)(this->vbo_size)); // Color attribute for data1
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(5, color_dimensions, GL_FLOAT, GL_FALSE, total_dimensions * sizeof(float), (void*)(this->vbo_size + color1_size)); // Color attribute for data2
    glEnableVertexAttribArray(5);

    // Update VBO size
    this->vbo_size = total_size;

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
*/
