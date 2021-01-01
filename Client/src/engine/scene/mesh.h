#pragma once

#include <ocode.h>

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "material.h"

namespace engine {
	class Mesh {
	private:
		Array array;
		ElementBuffer element_array;
		ArrayBuffer<float, 3> vertex_array;
		ArrayBuffer<float, 4, 4, 1> instance_array;

		uint32 elements;

		std::vector<glm::mat4> instance_translations;

	public:
		Mesh(Material* material);
		Mesh(std::vector<glm::vec3> vertexes, std::vector<uint32> elements, Material* material);
		~Mesh();

		void draw();

		uint32 new_instance(glm::mat4 translation);

		void delete_instance(uint32 index);

		void update_instance(uint32 index, glm::mat4 translation);

		uint64 instance_count();
	};
}