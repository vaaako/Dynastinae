#include "Dynastinae/scenes/scene3d.hpp"


Scene3D::Scene3D(Camera& camera)
	: Scene(camera.get_width(), camera.get_height()), camera(camera) {
	this->init_shaders();
}
//
// void Scene3D::draw_3d(const Shape3D& shape, const ShaderProgram& shader,
// 	const Texture* texture, const glm::vec3& pos, const Color& color,
// 	const float rotate, const glm::vec3& axis, const DrawMode draw_mode) const {
//
// 	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(draw_mode));
//
// 	// Use shader
// 	shader.use();
//
// 	// Init matrices
// 	glm::mat4 model = glm::mat4(1.0f);
// 	glm::mat4 view = glm::mat4(1.0f);
// 	glm::mat4 proj = glm::mat4(1.0f);
//
// 	// Model matrix //
// 	model = glm::translate(model, pos);
// 	model = glm::rotate(model, glm::radians(rotate), axis);
//
// 	// View matrix //
// 	view = glm::lookAt(camera.position, (camera.position + camera.orientation), camera.up);
//
// 	// Projection matrix //
// 	proj = glm::perspective(glm::radians(camera.fov), static_cast<float>(camera.get_width()) / static_cast<float>(camera.get_height()), camera.near_plane, camera.far_plane);
//
// 	// Add perspective
// 	proj = glm::perspective(glm::radians(camera.fov),
// 			(static_cast<float>(camera.get_width()) / static_cast<float>(camera.get_height())), camera.near_plane, camera.far_plane);
//
// 	// Apply changes
// 	shader.set_matrix4f("mvp", proj * view * model);
// 	shader.set_vector4f("shapeColor", { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f });
//
// 	// If using texture, bind texture
// 	if(texture != nullptr) {
// 		texture->bind();
// 	}
//
// 	// bind and draw
// 	shape.vao->bind();
// 	glDrawElements(GL_TRIANGLES, static_cast<int>(shape.indices_size), GL_UNSIGNED_INT, (void*)0);
// }
//
