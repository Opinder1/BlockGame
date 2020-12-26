#include "polygon2d.h"

std::vector<glm::vec2> square = {
	{0.5f, -0.5f},
	{-0.5f, 0.5f},
	{-0.5f, -0.5f},

	{0.5f, -0.5f},
	{-0.5f, 0.5f},
	{0.5f, 0.5f}
};

namespace engine {
	Polygon2D::Polygon2D() : Polygon2D(square) {}

	Polygon2D::Polygon2D(std::vector<glm::vec2> data) : vertexes(data), material(NULL) {

		int pos_index = 0; //glGetAttribLocation("vertex_position")
		int instance_index = 1; //glGetAttribLocation("instance_translation")

		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
		 
		glEnableVertexAttribArray(pos_index);
		glVertexAttribPointer(pos_index, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

		glGenBuffers(1, &instance_translation_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * instance_translations.size(), instance_translations.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(instance_index);
		glVertexAttribPointer(instance_index, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		glVertexAttribDivisor(instance_index, 1);
	}

	Polygon2D::~Polygon2D() {
		glDeleteBuffers(1, &vertex_buffer_id);
		glDeleteBuffers(1, &instance_translation_buffer_id);
		glDeleteVertexArrays(1, &vertex_array_id);
	}

	void Polygon2D::draw() {
		glBindVertexArray(vertex_array_id);
		//glDrawArrays(GL_TRIANGLES, 0, (uint32)vertexes.size());
		glDrawArraysInstanced(GL_TRIANGLES, 0, (uint32)vertexes.size(), (uint32)instance_translations.size());
	}

	uint32 Polygon2D::new_instance(glm::vec2 translation) {
		instance_translations.push_back(translation);

		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, instance_translations.size(), instance_translations.data(), GL_STATIC_DRAW);

		return (uint32)instance_translations.size() - 1;
	}

	void Polygon2D::delete_instance(uint32 index) {
		instance_translations.erase(instance_translations.begin() + index);

		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, instance_translations.size(), instance_translations.data(), GL_STATIC_DRAW);
	}

	void Polygon2D::update_instance(uint32 index, glm::vec2 translation) {
		instance_translations.at(index) = translation;

		glBindBuffer(GL_ARRAY_BUFFER, instance_translation_buffer_id);
	}
}