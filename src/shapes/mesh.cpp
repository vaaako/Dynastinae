#include "Dynastinae/shapes/mesh.hpp"
#include "Dynastinae/opengl/ebo.hpp"
#include "Dynastinae/opengl/shader_program.hpp"
#include "Dynastinae/opengl/vbo.hpp"
#include "Dynastinae/scenes/scene.hpp"
#include "Dynastinae/utils/log.hpp"
#include "Dynastinae/utils/string.hpp"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <unordered_map>


Mesh::Mesh() : indices_size(0) {}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
	: indices_size(static_cast<GLsizei>(indices.size())) {

	if(vertices.empty() || indices.empty()) {
		LOG_ERROR("\"vertices\" or \"indices\" is empty");
		throw;
	}

	this->vao->bind();

	// Calc total dimension size
	const uint8 pos_dim = 3; // To avoid using raw number and I confunsing myself
	const uint8 tex_dim = 2;
	const int total_size = (pos_dim + tex_dim) * sizeof(float); // need to be float

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

Mesh::Mesh(const std::string& path) {
	std::vector<uint32> indices;
	std::vector<Vertex> vertices =  this->load_obj(path, indices, this->has_texuv);

	this->indices_size = static_cast<GLsizei>(indices.size());
	// this->vertices_size = static_cast<GLsizei>(vertices.size());

	this->vao->bind();
	// Calc total dimension size
	const uint8 pos_dim = 3; // To avoid using raw number and I confunsing myself
	const uint8 tex_dim = 2;
	const int total_size = (pos_dim + tex_dim) * sizeof(float);
	
	// EBO is not necessary in this case
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


// void Mesh::draw2d(const Scene2D scene2d, const DrawMode drawmode, const uint32 drawtype) const {
// 	const ShaderProgram& shader = (this->texture != nullptr) ? scene2d.get_shader_texture() : scene2d.get_shader();
// 	this->draw2d(shader, drawmode, drawtype);
// }

// void Mesh::draw3d(const Scene3D scene3d, const DrawMode drawmode, const uint32 drawtype) const {
// 	const Camera& camera = scene3d.get_camera();
// 	const ShaderProgram& shader = (this->texture != nullptr) ? scene3d.get_shader_texture() : scene3d.get_shader();
//
// 	this->draw3d(camera, shader, drawmode, drawtype);
// }




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



std::vector<Vertex> Mesh::load_obj(const std::string& path, std::vector<uint32>& out_indices, bool& has_texuv) {
	if(StringHelper::file_extension(path) != "obj") {
		LOG_ERROR("Only obj files are supported!");
		throw;
	}

	std::ifstream file = std::ifstream(path);
	if(!file.is_open()) {
		LOG_ERROR("File %s was not opened", path.c_str());
		throw;
	}

	// To build vertices
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_texuvs;
	// std::vector<glm::vec3> temp_normals;

	// To build vertices and indices
	std::vector<Face> faces;

	std::string line;
	while(std::getline(file, line)) {
		std::istringstream iss = std::istringstream(line);
		std::string header; // First word
		iss >> header;

		// Case: v x y z
		if(header == "v") {
			glm::vec3 vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}

		// Case: vt u v
		else if(header == "vt") {
			glm::vec2 texuv;
			iss >> texuv.x >> texuv.y;
			temp_texuvs.push_back(texuv);
		}

		// Case: vn x y z


		// Case: faces, see below
		else if(header == "f") {
			std::string token;
			std::vector<std::string> face_tokens;

			// Get all tokens in face (split by space)
			while(iss >> token) {
				face_tokens.push_back(token);
			}

			if(face_tokens.size() != 3) {
				LOG_ERROR("Only triangular faces are supported. Try changing model export configuration");
				throw;
			}

			Face face;
			/*
			* Cases:
			* 1: f v/vt/vn v/vt/vn v/vt/vn
			* 2: f v/vt v/vt v/vt
			* 3: f v//vn v//vn v//vn
			*/
			if(face_tokens.at(0).find('/') != std::string::npos) {
				for(size_t i = 0; i < face_tokens.size(); i++) {
					std::istringstream sub = std::istringstream(face_tokens.at(i));
					std::string str_vertex_index, str_texuv_index;

					// Get vertex and add to face
					std::getline(sub, str_vertex_index, '/');
					face.vertex_index[i] = std::stoi(str_vertex_index); 

					// Case 3 has no texture indice
					if(std::getline(sub, str_texuv_index, '/')) {
						face.texuv_index[i] = std::stoi(str_texuv_index);
					}

					// Case 2 has no normal map indice
					// if(std::getline(sub, str_normal_index, '/')) {
					// 	face.normal_index[i] = std::stoi(str_normal_index);
					// }
				}

			// Case: f v1 v2 v3
			} else {
				face.vertex_index[0] = std::stoi(face_tokens.at(0));
				face.vertex_index[1] = std::stoi(face_tokens.at(1));
				face.vertex_index[2] = std::stoi(face_tokens.at(2));
			}

			faces.push_back(face);

			// NOTE -- i could build vertices and indices here
		}
	} // end while loop

	file.close();

	// No texture uv
	has_texuv = !temp_texuvs.empty();

	// Build vertices and generate indices
	std::unordered_map<Vertex, uint32> vertex_map; // Store unique vertices and corresponding indices
	std::vector<Vertex> out_vertices;
	for(const Face& face : faces) {
		for(size_t i = 0; i < 3; i++) {
			// Build vertices
			Vertex vertex = {
				.position = temp_vertices.at(static_cast<uint32>(face.vertex_index.at(i) - 1)),

				// Check for case 2 or 3 of face
				.texuv = (has_texuv && face.texuv_index[i] != 0)
								? temp_texuvs.at(static_cast<uint32>(face.texuv_index.at(i) - 1))
								: glm::vec2(0) 
				// Do the same for normal map
			};

			// Generate indices

			// Check if vertex is alredy calculated
			auto it = vertex_map.find(vertex);

			// Found
			if(it != vertex_map.end()) {
				uint32 index = it->second; // Use existing index ("newindex" below)
				out_indices.push_back(index);

			// Not found
			} else {
				out_vertices.push_back(vertex);

				// Calculate indice
				uint32 newindex = static_cast<uint32>(out_vertices.size() - 1);
				out_indices.push_back(newindex);
				vertex_map[vertex] = newindex; // Register vertex
			}
		}
	}

	return out_vertices;
}

