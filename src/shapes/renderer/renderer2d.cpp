#include "../../../include/shapes/renderer/renderer2d.hpp"
#include "../../../include/window/window.hpp"

//
// Renderer2D::Renderer2D() {
// 	const std::vector<float> tri_vert = {
// 		// VERTICES / TEXTURE
// 		1.0f, 1.0f,   0.0f, 0.0f, // Bottom Right
// 		0.0f, 1.0f,   1.0f, 0.0f, // Bottom Left
// 		0.5f, 0.0f,   0.5f, 1.0f  // Middle
// 	};
//
// 	const std::vector<float> rec_vert = {
// 		// VERTICES / TEXTURE
// 		0.0f, 0.0f,   1.0f, 1.0f, // Bottom Left
// 		1.0f, 0.0f,   0.0f, 1.0f, // Bottom Right
// 		1.0f, 1.0f,   0.0f, 0.0f, // Top Right
// 		0.0f, 1.0f,   1.0f, 0.0f  // Top Left
// 	};
//
// 	const std::vector<unsigned int> indices = {
// 		// 0, 1, 2, // First triangle
// 		// 0, 2, 3  // Second triangle
// 		0, 1, 2, // First triangle
// 		2, 3, 0  // Second triangle
// 	};
//
//
// 	this->vao = std::make_unique<VAO>();
// 	this->vbo = std::make_unique<VBO>();
// 	this->vbo->store_data(tri_vert, rec_vert, 2, 2); // Store two vertices on the same VBO
// 	this->ebo = std::make_unique<const EBO>(indices); // Since Rectangle indices starts with Triangle indices, I can upload only Rectangle indices
//
// 	// Make camera
// 	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::static_width()), 
// 		static_cast<float>(Window::static_height()), 0.0f, -1.0f, 1.0f);
//
// 	this->shader = std::make_unique<const ShaderProgram>(this->vertex_shader, this->fragment_shader);
// 	this->shader_texture = std::make_unique<const ShaderProgram>(this->vertex_shader_texture, this->fragment_shader_texture);
//
// 	// If don't do "use", "set" order like this, shaders won't work
// 	this->shader->use();
// 	this->shader->set_matrix4f("projection", projection);
//
// 	this->shader_texture->use();
// 	this->shader_texture->set_matrix4f("projection", projection);
// }
//
