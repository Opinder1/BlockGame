#pragma once

#include <ocode.h>

#include <vector>

#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "material.h"

namespace engine {
	class Mesh {
	protected:
		ElementArray array;
		ArrayBuffer vertex_array;
		ArrayBuffer normal_array;
		ArrayBuffer texcoord_array;

	public:
		Mesh();
		Mesh(std::vector<glm::uint16> elements, std::vector<glm::vec3> vertexes, std::vector<glm::vec3> normals, std::vector<glm::vec2> texcoords);
		~Mesh();

		void draw();
		void draw_instanced(glm::uint32 instance_count);
	};
}