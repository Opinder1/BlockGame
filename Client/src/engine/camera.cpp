#include "camera.h"

namespace engine {
	Camera::Camera(float fov, float width, float height, float near, float far) {
		set_perspective(fov, width, height, near, far);
	}

	Camera::~Camera() {

	}

	void Camera::set_perspective(float fov, float width, float height, float near, float far) {
		//projection = glm::infinitePerspective(fov, width / height, near);
		projection = glm::perspectiveFov(glm::radians(fov), width, height, near, far);
	}

	void Camera::translate(glm::vec3 translation) {
		translation = glm::rotate(translation, -rotation.y, glm::vec3(0, 1, 0));

		position += 0.5 * translation;
	}

	void Camera::rotate(float _rotation, glm::vec3 axis) {
		rotation += _rotation * axis;
	}

	const glm::mat4& Camera::get_projection() {

		glm::vec3 v(cos(rotation.x) * cos(rotation.y), -sin(rotation.x), cos(rotation.x) * sin(rotation.y));

		glm::mat4 view = glm::lookAt(
			position,
			position + v,
			glm::vec3(0, 1, 0)
		);

		return projection * view;
	}
}