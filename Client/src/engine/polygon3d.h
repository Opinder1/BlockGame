#pragma once

#include <ocode.h>

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "material.h"

namespace engine {
	class Polygon3D {
	private:
		uint32 vertex_array_id;

		std::vector<glm::vec3> vertexes;
		uint32 vertex_buffer_id;

		std::vector<glm::mat4> instance_translations;
		uint32 instance_translation_buffer_id;

		Material* material;

	public:
		Polygon3D(const Polygon3D&) = delete;
		Polygon3D();
		Polygon3D(std::vector<glm::vec3> data);
		~Polygon3D();

		void draw();

		uint32 new_instance(glm::mat4 translation);

		void delete_instance(uint32 index);

		void update_instance(uint32 index, glm::mat4 translation);
	};
}