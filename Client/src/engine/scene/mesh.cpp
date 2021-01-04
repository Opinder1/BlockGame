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

std::vector<uint8> cube_elements = {
	0, 1, 2,
	3, 1, 2,
	4, 0, 5,
	1, 0, 5,
	5, 1, 7,
	3, 1, 7,
	7, 3, 6,
	2, 3, 6,
	6, 2, 4,
	0, 2, 4,
	4, 5, 6,
	7, 5, 6
};

std::vector<glm::vec3> cube_vertexes = {
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, 0.5f, 0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f}
};

namespace engine {
	Mesh::Mesh(Material* material) : Mesh(cube_elements, cube_vertexes, material) {}

	Mesh::Mesh(std::vector<uint8> elements, std::vector<glm::vec3> vertexes, Material* material) {
		vertex_array.format<float, 3>(material->get_attribute("vertex_position"));

		array.data((uint32)elements.size(), elements.data(), BufferType::STATIC);
		vertex_array.data((uint32)vertexes.size(), vertexes.data(), BufferType::STATIC);
	}

	Mesh::~Mesh() {
	}

	void Mesh::draw(uint32 instance_count) {
		array.draw_elements_instanced((uint32)array.get_size(), instance_count);
	}
}