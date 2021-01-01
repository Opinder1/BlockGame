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

std::vector<uint32> cube_elements = {
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

namespace engine {
	Mesh::Mesh(Material* material) : Mesh(cube_vertexes, cube_elements, material) {}

	Mesh::Mesh(std::vector<glm::vec3> vertexes, std::vector<uint32> elements, Material* material) :
		array(),
		element_array(),
		vertex_array(material->get_attribute("vertex_position")),
		instance_array(material->get_attribute("instance_translation")),
		elements(elements.size())
	{
		vertex_array.data(vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
		element_array.data(elements.size(), elements.data(), GL_STATIC_DRAW);
		instance_array.data(0, vertexes.data(), GL_DYNAMIC_DRAW);
	}

	Mesh::~Mesh() {

	}

	void Mesh::draw() {
		array.draw_elements_instanced(GL_TRIANGLES, elements, instance_translations.size());
	}

	uint32 Mesh::new_instance(glm::mat4 translation) {
		size_t size = instance_translations.capacity();
		instance_translations.push_back(translation);

		if (instance_translations.capacity() != size) {
			instance_array.data(instance_translations.capacity(), instance_translations.data(), GL_DYNAMIC_DRAW);
		}
		else {
			instance_array.sub_data(instance_translations.size() - 1, 1, instance_translations.data());
		}

		return (uint32)instance_translations.size() - 1;
	}

	void Mesh::delete_instance(uint32 index) {
		size_t size = instance_translations.capacity();

		instance_translations.erase(instance_translations.begin() + index);

		instance_array.sub_data(index, instance_translations.size() - index, instance_translations.data());
	}

	void Mesh::update_instance(uint32 index, glm::mat4 translation) {
		instance_translations.at(index) = translation;

		instance_array.sub_data(index, 1, instance_translations.data());
	}

	uint64 Mesh::instance_count() {
		return instance_translations.size();
	}
}