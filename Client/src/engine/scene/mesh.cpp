#include "mesh.h"

std::vector<glm::uint16> cube_elements = {
	0, 2, 1,
	0, 3, 2,
	1, 2, 6,
	6, 5, 1,
	4, 5, 6,
	6, 7, 4,
	2, 3, 6,
	6, 3, 7,
	0, 7, 3,
	0, 4, 7,
	0, 1, 5,
	0, 5, 4
};

std::vector<glm::vec3> cube_vertexes = {
	{-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, -0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f}
};

std::vector<glm::vec3> cube_normals = {

};

std::vector<glm::vec2> cube_texcoords = {

};

namespace engine {
	Mesh::Mesh() : Mesh(cube_elements, cube_vertexes, cube_normals, cube_texcoords) {}

	Mesh::Mesh(std::vector<glm::uint16> elements, std::vector<glm::vec3> vertexes, std::vector<glm::vec3> normals, std::vector<glm::vec2> texcoords) {
		array._new(Type::uint16);
		vertex_array._new();
		normal_array._new();
		texcoord_array._new();

		array.set_attribute(0, vertex_array, Type::float32, 3);
		array.set_attribute(1, normal_array, Type::float32, 3);
		array.set_attribute(2, texcoord_array, Type::float32, 3);

		size = (glm::uint32)elements.size();

		array.set_data(elements.size(), elements.data(), BufferType::Static);
		vertex_array.set_data(vertexes.size(), vertexes.data(), BufferType::Static);
		normal_array.set_data(normals.size(), normals.data(), BufferType::Static);
		texcoord_array.set_data(texcoords.size(), texcoords.data(), BufferType::Static);
	}

	Mesh::~Mesh() {
		vertex_array._delete();
		normal_array._delete();
		texcoord_array._delete();
	}

	void Mesh::draw() {
		array.draw(size);
	}

	void Mesh::draw_instanced(glm::uint32 instance_count) {
		array.draw_instanced(size, instance_count);
	}
}