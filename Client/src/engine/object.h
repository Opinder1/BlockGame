#pragma once

namespace engine {
	struct Object {
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

		Object() : scale(1) {}
	};
}