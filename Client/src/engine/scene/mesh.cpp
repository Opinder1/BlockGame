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

namespace engine {
	Mesh::Mesh(Material* material) : Mesh(cube, material) {}

	Mesh::Mesh(std::vector<glm::vec3> data, Material* material) : 
		vertexes(data), 
		object(), 
		vertex_buffer(GL_ARRAY_BUFFER), 
		instance_buffer(GL_ARRAY_BUFFER)
	{
		int pos_index = material->get_attribute("vertex_position");
		int instance_index = material->get_attribute("instance_translation");

		vertex_buffer.type_vec<glm::vec3>(pos_index);
		vertex_buffer.data(vertexes.size(), vertexes.data(), GL_STATIC_DRAW);

		instance_buffer.type_mat<glm::mat4>(instance_index);
		instance_buffer.divisor_mat<glm::mat4>(instance_index, 1);
		instance_buffer.data(0, vertexes.data(), GL_DYNAMIC_DRAW);
	}

	Mesh::~Mesh() {

	}

	void Mesh::draw() {
		object.draw_instances(GL_TRIANGLE_STRIP, vertexes.size(), instance_translations.size());
	}

	uint32 Mesh::new_instance(glm::mat4 translation) {
		size_t size = instance_translations.capacity();
		instance_translations.push_back(translation);

		if (instance_translations.capacity() != size) {
			instance_buffer.data(instance_translations.capacity(), instance_translations.data(), GL_DYNAMIC_DRAW);
		}
		else {
			instance_buffer.sub_data(instance_translations.size() - 1, 1, instance_translations.data());
		}

		return (uint32)instance_translations.size() - 1;
	}

	void Mesh::delete_instance(uint32 index) {
		size_t size = instance_translations.capacity();

		instance_translations.erase(instance_translations.begin() + index);

		instance_buffer.sub_data(index, instance_translations.size() - index, instance_translations.data());
	}

	void Mesh::update_instance(uint32 index, glm::mat4 translation) {
		instance_translations.at(index) = translation;

		instance_buffer.sub_data(index, 1, instance_translations.data());
	}

	uint64 Mesh::instance_count() {
		return instance_translations.size();
	}
}