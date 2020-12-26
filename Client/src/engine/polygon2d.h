#pragma once

#include <ocode.h>

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "material.h"

namespace engine {
	class Polygon2D {
	private:
		uint32 vertex_array_id;

		std::vector<glm::vec2> vertexes;
		uint32 vertex_buffer_id;

		std::vector<glm::vec2> instance_translations;
		uint32 instance_translation_buffer_id;

		Material* material;

	public:
		Polygon2D(const Polygon2D&) = delete;
		Polygon2D();
		Polygon2D(std::vector<glm::vec2> data);
		~Polygon2D();

		void draw();

		uint32 new_instance(glm::vec2 translation);

		void delete_instance(uint32 index);

		void update_instance(uint32 index, glm::vec2 translation);
	};
}