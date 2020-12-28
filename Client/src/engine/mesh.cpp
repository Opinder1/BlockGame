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

	Mesh::Mesh(std::vector<glm::vec3> data, Material* material) : vertexes(data) {
		int pos_index = material->get_attribute("vertex_position");
		int instance_index = material->get_attribute("instance_translation");

		bind_buffer(GL_ARRAY_BUFFER, 0);
		buffer_data(GL_ARRAY_BUFFER, vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
		buffer_type_vec<3>(pos_index, GL_FLOAT);

		bind_buffer(GL_ARRAY_BUFFER, 1);
		buffer_data(GL_ARRAY_BUFFER, vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
		buffer_type_mat<4, 4>(instance_index, GL_FLOAT);
	}

	Mesh::~Mesh() {

	}

	void Mesh::draw() {
		bind();
		draw_instances(GL_TRIANGLES, vertexes.size(), instance_translations.size());
	}

	uint32 Mesh::new_instance(glm::mat4 translation) {
		size_t size = instance_translations.capacity();

		instance_translations.push_back(translation);

		bind_buffer(GL_ARRAY_BUFFER, 1);
		if (instance_translations.capacity() != size) {
			buffer_data(GL_ARRAY_BUFFER, instance_translations.capacity(), instance_translations.data(), GL_STATIC_DRAW);
		}
		else {
			buffer_sub_data(GL_ARRAY_BUFFER, instance_translations.size() - 1, instance_translations.data());
		}

		return (uint32)instance_translations.size() - 1;
	}

	void Mesh::delete_instance(uint32 index) {
		size_t size = instance_translations.capacity();

		instance_translations.erase(instance_translations.begin() + index);

		bind_buffer(GL_ARRAY_BUFFER, 1);
		buffer_data(GL_ARRAY_BUFFER, instance_translations.capacity(), instance_translations.data(), GL_STATIC_DRAW);
	}

	void Mesh::update_instance(uint32 index, glm::mat4 translation) {
		instance_translations.at(index) = translation;

		buffer_sub_data(GL_ARRAY_BUFFER, index, instance_translations.data());
	}

	uint64 Mesh::instance_count() {
		return instance_translations.size();
	}
}