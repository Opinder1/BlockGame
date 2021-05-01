#pragma once

#include <GLM/glm.hpp>

namespace engine {
	struct Transform2D {
		glm::vec2 position;
		float rotation;
		float scale;

		Transform2D(glm::vec2 position = glm::vec2(0), float rotation = 0, float scale = 1) : position(position), rotation(rotation), scale(scale) {}

		void move(const glm::vec2& r);
		void rotate(float r);
		void rescale(float r);

		glm::mat3 as_transform();
	};

	struct Transform3D {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform3D(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1)) : position(position), rotation(rotation), scale(scale) {}

		void move(const glm::vec3& r);
		void rotate(const glm::vec3& r);
		void rescale(const glm::vec3& r);

		float width() { return scale.x; }
		float height() { return scale.y; }
		float depth() { return scale.z; }

		glm::mat4 as_transform();

		inline glm::mat3 get_a() { return glm::mat3(1, 0, 0, 0, cos(rotation.x), sin(rotation.x), 0, -sin(rotation.x), cos(rotation.x)); }
		inline glm::mat3 get_b() { return glm::mat3(cos(rotation.y), 0, -sin(rotation.y), 0, 1, 0, sin(rotation.y), 0, cos(rotation.y)); }
		inline glm::mat3 get_c() { return glm::mat3(cos(rotation.z), sin(rotation.z), 0, -sin(rotation.z), cos(rotation.z), 0, 0, 0, 1); }

		inline glm::mat3 get_d() { return get_a() * get_b() * get_c(); }
	};
}