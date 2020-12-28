#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "object.h"

namespace engine {
	class Camera : public Object {
	private:
		glm::mat4 projection;

	public:
		Camera(float fov, float width, float height, float near, float far);
		~Camera();

		void set_perspective(float fov, float width, float height, float near, float far);

		void translate(glm::vec3 translation);
		void rotate(float rotation, glm::vec3 axis);

		const glm::mat4& get_projection();

		inline glm::mat3 get_a() {
			return glm::mat3(1, 0, 0, 0, cos(rotation.x), sin(rotation.x), 0, -sin(rotation.x), cos(rotation.x));
		}

		inline glm::mat3 get_b() {
			return glm::mat3(cos(rotation.y), 0, -sin(rotation.y), 0, 1, 0, sin(rotation.y), 0, cos(rotation.y));
		}

		inline glm::mat3 get_c() {
			return glm::mat3(cos(rotation.z), sin(rotation.z), 0, -sin(rotation.z), cos(rotation.z), 0, 0, 0, 1);
		}

		inline glm::mat3 get_d() {
			return glm::mat3(cos(rotation.z) * cos(rotation.y), sin(rotation.z) * cos(rotation.y), -sin(rotation.y), cos(rotation.z) * sin(rotation.y) * sin(rotation.x) - sin(rotation.z) * cos(rotation.x), sin(rotation.z) * sin(rotation.y) * sin(rotation.x) + cos(rotation.z) * cos(rotation.x), cos(rotation.y) * sin(rotation.x), cos(rotation.z) * sin(rotation.y) * cos(rotation.x) + sin(rotation.z) * sin(rotation.x), sin(rotation.z) * sin(rotation.y) * cos(rotation.x) - cos(rotation.z) * sin(rotation.x), cos(rotation.y) * cos(rotation.x));
		}
	};
}