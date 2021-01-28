#pragma once

#include <GLM/glm.hpp>

namespace engine {
	struct Transform2D {
		glm::vec2 position;
		glm::float1 rotation;
		glm::vec2 scale;

		Transform2D() : position(0), rotation(0), scale(1) {}
		Transform2D(glm::vec2 position, glm::float1 rotation, glm::vec2 scale) : position(position), rotation(rotation), scale(scale) {}

		void move(const glm::vec2& r);
		void rotate(glm::float1 r);
		void rescale(const glm::vec2& r);

		glm::mat3 as_transform();
	};

	struct Transform3D {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform3D() : position(0), rotation(0), scale(1) {}
		Transform3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : position(position), rotation(rotation), scale(scale) {}

		void move(const glm::vec3& r);
		void rotate(const glm::vec3& r);
		void rescale(const glm::vec3& r);

		glm::mat4 as_transform();

		inline glm::mat3 get_a() { return glm::mat3(1, 0, 0, 0, cos(rotation.x), sin(rotation.x), 0, -sin(rotation.x), cos(rotation.x)); }
		inline glm::mat3 get_b() { return glm::mat3(cos(rotation.y), 0, -sin(rotation.y), 0, 1, 0, sin(rotation.y), 0, cos(rotation.y)); }
		inline glm::mat3 get_c() { return glm::mat3(cos(rotation.z), sin(rotation.z), 0, -sin(rotation.z), cos(rotation.z), 0, 0, 0, 1); }

		inline glm::mat3 get_d() { return get_a() * get_b() * get_c(); }
	};
}