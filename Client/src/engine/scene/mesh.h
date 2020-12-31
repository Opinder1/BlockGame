#pragma once

#include <ocode.h>

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "../renderer/gpuarray.h"
#include "../renderer/gpubuffer.h"
#include "material.h"

namespace engine {
	class Mesh {
	private:
		GPUArray array;
		GPUArrayBuffer<float, 3> vertex_array;
		GPUArrayBuffer<float, 4, 4, 1> instance_array;

		std::vector<glm::vec3> vertexes;

		std::vector<glm::mat4> instance_translations;

	public:
		Mesh(Material* material);
		Mesh(std::vector<glm::vec3> data, Material* material);
		~Mesh();

		void draw();
		 
		uint32 new_instance(glm::mat4 translation);

		void delete_instance(uint32 index);

		void update_instance(uint32 index, glm::mat4 translation);

		uint64 instance_count();
	};
}