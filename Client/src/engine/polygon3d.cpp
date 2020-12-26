#include "polygon3d.h"

std::vector<glm::vec3> cube = {
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, 0.5f, 0.5f},
	{-0.5f, -0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, -0.5f},
	{-0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f}
};

namespace engine {
	Polygon3D::Polygon3D() : Polygon3D(cube) {}

	Polygon3D::Polygon3D(std::vector<glm::vec3> data) : vertexes(data), material(NULL) {
		int pos_index = 0; //glGetAttribLocation("vertex_position")
		int instance_index = 1; //glGetAttribLocation("instance_translation")

		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(pos_index);
		glVertexAttribPointer(pos_index, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &instance_translation_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instance_translations.size(), instance_translations.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(instance_index);
		glVertexAttribPointer(instance_index, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), 0);
		glVertexAttribDivisor(instance_index, 1);

		glEnableVertexAttribArray(instance_index + 1);
		glVertexAttribPointer(instance_index + 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
		glVertexAttribDivisor(instance_index + 1, 1);

		glEnableVertexAttribArray(instance_index + 2);
		glVertexAttribPointer(instance_index + 2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
		glVertexAttribDivisor(instance_index + 2, 1);

		glEnableVertexAttribArray(instance_index + 3);
		glVertexAttribPointer(instance_index + 3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(instance_index + 3, 1);
	}

	Polygon3D::~Polygon3D() {
		glDeleteBuffers(1, &vertex_buffer_id);
		glDeleteBuffers(1, &instance_translation_buffer_id);
		glDeleteVertexArrays(1, &vertex_array_id);
	}

	void Polygon3D::draw() {
		glBindVertexArray(vertex_array_id);
		//glDrawArrays(GL_TRIANGLES, 0, (uint32)vertexes.size());
		glDrawArraysInstanced(GL_TRIANGLES, 0, (uint32)vertexes.size(), (uint32)instance_translations.size());
	}

	uint32 Polygon3D::new_instance(glm::mat4 translation) {
		instance_translations.push_back(translation);

		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instance_translations.size(), instance_translations.data(), GL_STATIC_DRAW);

		return (uint32)instance_translations.size() - 1;
	}

	void Polygon3D::delete_instance(uint32 index) {
		instance_translations.erase(instance_translations.begin() + index);

		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instance_translations.size(), instance_translations.data(), GL_STATIC_DRAW);
	}

	void Polygon3D::update_instance(uint32 index, glm::mat4 translation) {
		instance_translations.at(index) = translation;

		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
	}
}