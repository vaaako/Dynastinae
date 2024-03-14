#include "../../include/opengl/ebo.hpp"

EBO::EBO(const std::vector<unsigned int>& indices) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}


EBO::EBO(const std::vector<unsigned int>& indices, const std::vector<unsigned int>& indices2) {
	// Make one array
	std::vector<unsigned int> intercalated_data;
	intercalated_data.reserve(indices.size() + indices2.size()); // Reserve space to avoid reallocation
	intercalated_data.insert(intercalated_data.end(), indices.begin(), indices.end());
	intercalated_data.insert(intercalated_data.end(), indices2.begin(), indices2.end());


	// Create and bind EBO
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, intercalated_data.size() * sizeof(unsigned int), intercalated_data.data(), GL_STATIC_DRAW);

	this->unbind();
}
