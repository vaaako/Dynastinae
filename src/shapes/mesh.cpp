#include "Dynastinae/shapes/mesh.hpp"
#include "Dynastinae/opengl/ebo.hpp"
#include "Dynastinae/opengl/shader_program.hpp"
#include "Dynastinae/opengl/vbo.hpp"
#include "Dynastinae/scenes/scene.hpp"
#include "Dynastinae/scenes/scene2d.hpp"
#include "Dynastinae/scenes/scene3d.hpp"
#include "Dynastinae/utils/log.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
	: indices_size(indices.size()) {

	if(vertices.empty() || indices.empty()) {
		LOG_ERROR("\"vertices\" or \"indices\" is empty");
		throw;
	}

	this->vao->bind();

	// Calc total dimension size
	const uint8 pos_dim = 3; // To avoid using raw number and I confunsing myself
	const uint8 tex_dim = 2;
	const int total_size = (pos_dim + tex_dim) * sizeof(float);

	// Make VBO and EBO object to construct on VAO
	VBO vbo = VBO();
	EBO ebo = EBO(indices);

	// Build VBO
	vbo.alloc_data(vertices.size() * sizeof(Vertex), vertices.data());
	vbo.link_attrib(0, pos_dim, total_size, 0);       // Position
	vbo.link_attrib(1, tex_dim, total_size, pos_dim); // Texture

	this->vao->unbind();
	vbo.unbind();
	ebo.unbind();
}


void Mesh::draw2d(const Scene2D scene2d, const DrawMode drawmode, const uint32 drawtype) const {
	const ShaderProgram& shader = (this->texture != nullptr) ? scene2d.get_shader_texture() : scene2d.get_shader();
	this->draw2d(shader, drawmode, drawtype);
}

void Mesh::draw3d(const Scene3D scene3d, const DrawMode drawmode, const uint32 drawtype) const {
	const Camera& camera = scene3d.get_camera();
	const ShaderProgram& shader = (this->texture != nullptr) ? scene3d.get_shader_texture() : scene3d.get_shader();

	this->draw3d(camera, shader, drawmode, drawtype);
}




void Mesh::draw2d(const ShaderProgram& shader, const DrawMode drawmode, const uint32 drawtype) const {
	this->draw_start(shader, drawmode);

	glm::mat4 model = glm::mat4(1.0f);

	// Move, Resize and rotate
	model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.0f));         // Translate position
	model = glm::translate(model, glm::vec3(0.5f * this->size.x, 0.5f * this->size.y, 0.0f));   // Origin from top-lef to center
	model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));         // Rotate
	model = glm::translate(model, glm::vec3(-0.5f * this->size.x, -0.5f * this->size.y, 0.0f)); // Origin back to top-left
	model = glm::scale(model, glm::vec3(this->size.x, this->size.y, 1.0f));                     // Resize

	// Apply changes
	shader.set_matrix4f("model", model);

	this->draw_end(shader, drawtype);
}

void Mesh::draw3d(const Camera& camera, const ShaderProgram& shader, const DrawMode drawmode, const uint32 drawtype) const {
	this->draw_start(shader, drawmode);

	// Init matrices
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	// Model matrix //
	model = glm::translate(model, this->position.to_glm());
	model = glm::rotate(model, glm::radians(this->angle), this->axis.to_glm());
	model = glm::scale(model, glm::vec3(this->size.x, this->size.y, this->size.z)); // Resize

	// View matrix //
	view = glm::lookAt(camera.position, (camera.position + camera.orientation), camera.up);

	// Projection matrix //
	proj = glm::perspective(glm::radians(camera.fov), static_cast<float>(camera.get_width()) / static_cast<float>(camera.get_height()), camera.near_plane, camera.far_plane);

	// Add perspective
	proj = glm::perspective(glm::radians(camera.fov),
			(static_cast<float>(camera.get_width()) / static_cast<float>(camera.get_height())), camera.near_plane, camera.far_plane);

	// Apply changes
	shader.set_matrix4f("mvp", proj * view * model);

	this->draw_end(shader, drawtype);
}

