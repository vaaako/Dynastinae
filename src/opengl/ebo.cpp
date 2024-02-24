#include "../../include/opengl/ebo.hpp"

EBO::EBO(const std::vector<unsigned int>& indices) {
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

// #include <iostream>

EBO::EBO(const std::vector<unsigned int>& indices, const std::vector<unsigned int>& indices2) {
	// Make one array
	std::vector<GLuint> intervaleted_data = indices;
	intervaleted_data.insert(intervaleted_data.end(), indices2.begin(), indices2.end());


	// for(int i = 0; i < intervaleted_data.size(); i++) {
	// 	if(i == 18) {
	// 		std::cout << "\n\n == CUBE ==\n" << std::endl;
	// 	}
	// 	std::cout << intervaleted_data.at(i) << " " << std::endl;
	// }

	// Create and bind EBO
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, intervaleted_data.size() * sizeof(GLuint), intervaleted_data.data(), GL_STATIC_DRAW);
}
