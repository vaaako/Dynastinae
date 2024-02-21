#include "../../include/opengl/vbo.hpp"
#include <cstdint>

VBO::VBO() {}

VBO::VBO(const std::vector<float>& data, const int position, const int dimension) {
	this->store_data(data, position, dimension);
}


void VBO::store_data(const std::vector<float>& data, const unsigned int position, const unsigned int dimensions) {
	glGenBuffers(1, &this->id); // BUG -- Do i need every time?? No?? So why don't work when i keep this on constructor???
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	// Configure the Vertex Attribute so OpenGl knows how to read the VBO
	glVertexAttribPointer(position, dimensions, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(position);     // Enabling Vertex Position to draw
	glBindBuffer(GL_ARRAY_BUFFER, this->id); // Unbind VBO
}


// TODO -- Modify to take only one data, "vertex count = 4", "vertex start from = 0"
// For two vertices on same VBO
void VBO::store_data(const std::vector<float>& data, const std::vector<float>& data2, const unsigned int dimensions) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);


	const long unsigned int data_size  = data.size() * sizeof(float);
	const long unsigned int data2_size = data2.size() * sizeof(float);
	const long unsigned int total_size = data_size + data2_size;

	// Allocate Memory
	glBufferData(GL_ARRAY_BUFFER, total_size, nullptr, GL_STATIC_DRAW);

	// Upload Data and Data2
	glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, data.data());
	glBufferSubData(GL_ARRAY_BUFFER, data_size, data2_size, data2.data());

	// Seet Data Vertex Attribute
	glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // position attribute
	glEnableVertexAttribArray(0);
	// Texture coordinate
	glVertexAttribPointer(1, dimensions, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(dimensions * sizeof(float))); // texture coords
	glEnableVertexAttribArray(1);



	// Set Data2 Vertex Attribute
	// Starting from where Data1 ends
	glVertexAttribPointer(2, dimensions, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(uintptr_t)(data_size)); // position attribute
	glEnableVertexAttribArray(2);
	// Texture coordinate
	glVertexAttribPointer(3, dimensions, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(uintptr_t)(data_size + dimensions)); // position attribute
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, this->id); // Unbind VBO
}

void VBO::store_two_data(const std::vector<float>& data, const unsigned int dimension1, const unsigned int dimension2) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);

	const long unsigned int data_size  = data.size() * sizeof(float);
	const int total_dimension = dimension1 + dimension2;


	// Allocate Memory
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);


	// Seet Data Vertex Attribute
	glVertexAttribPointer(0, dimension1, GL_FLOAT, GL_FALSE, total_dimension * sizeof(float), (void*)0); // position attribute
	glEnableVertexAttribArray(0);
	// Texture coordinate
	glVertexAttribPointer(1, dimension2, GL_FLOAT, GL_FALSE, total_dimension * sizeof(float), (void*)(dimension2 * sizeof(float))); // texture coords
	glEnableVertexAttribArray(1);

	// Allocate Memory
	glBindBuffer(GL_ARRAY_BUFFER, this->id); // Unbind VBO
}

