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
		ElementArray array;
		ArrayBuffer vertex_array;

	public:
		Mesh(Material* material);
		Mesh(std::vector<uint8> elements, std::vector<glm::vec3> vertexes, Material* material);
		~Mesh();

		void draw(uint32 instance_count);
	};
}