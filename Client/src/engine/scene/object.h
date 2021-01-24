#pragma once

#include "transform.h"

#include "mesh.h"

namespace engine {
	class Object {
	private:
		Transform3D transform;
		Mesh* mesh;

	public:
		glm::mat4 get_m();
	};
}