#include "mesh.h"

std::vector<glm::vec3> cube = {
	{-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
	{-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, -0.5f},
	{-0.5f, 0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}
};

std::vector<uint16> cube_elements = {
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

	Mesh::Mesh(std::vector<uint16> elements, std::vector<glm::vec3> vertexes, std::vector<glm::vec3> normals, std::vector<glm::vec2> texcoords) {
		vertex_array.format<float, 3>(0);
		normal_array.format<float, 3>(1);
		texcoord_array.format<float, 3>(2);

		array.data((uint32)elements.size(), elements.data(), BufferType::STATIC);
		vertex_array.data((uint32)vertexes.size(), vertexes.data(), BufferType::STATIC);
		normal_array.data((uint32)normals.size(), normals.data(), BufferType::STATIC);
		texcoord_array.data((uint32)texcoords.size(), texcoords.data(), BufferType::STATIC);
	}

	Mesh::~Mesh() {
	}

	void Mesh::draw() {
		array.draw((uint32)array.get_size());
	}

	void Mesh::draw_instanced(uint32 instance_count) {
		array.draw_instanced((uint32)array.get_size(), instance_count);
	}
}