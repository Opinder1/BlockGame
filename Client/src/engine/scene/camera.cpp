#include "camera.h"

namespace engine {
	//GlobalBuffer* camera_buf;

	Camera::Camera(float fov, float width, float height) {
		set_perspective(fov, width, height);
	}

	Camera::~Camera() {

	}

	void Camera::set_perspective(float fov, float width, float height) {
		//projection = glm::infinitePerspective(fov, width / height, near);
		projection = glm::perspectiveFov(glm::radians(fov), width, height, 0.1f, 1000000.0f);
	}

	glm::mat4 Camera::get_projection() {
		glm::mat4 view = glm::lookAt(
			position,
			position + look_direction(),
			up_direction()
		);

		return projection * view;
	}

	FPSCamera::FPSCamera(float fov) : Camera(fov, 1, 1), fov(fov), last_mouse_pos(0, 0) {
		engine::event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, FPSCamera::on_window_resize);
	}

	void FPSCamera::update(glm::vec2 mouse_pos) {
		glm::vec2 rot = mouse_pos - last_mouse_pos;

		rotation.x += (rot.x / 1000.0f);
		rotation.y = glm::clamp(rotation.y + (rot.y / 1000.0f), -1.57f, 1.57f);

		last_mouse_pos = mouse_pos;
	}

	glm::vec3 FPSCamera::look_direction() {
		return glm::vec3(cos(rotation.y) * cos(rotation.x), -sin(rotation.y), cos(rotation.y) * sin(rotation.x));
	}

	glm::vec3 FPSCamera::up_direction() {
		return glm::vec3(0, 1, 0);
	}

	glm::vec3 FPSCamera::left_direction() {
		return glm::normalize(glm::cross(look_direction(), up_direction()));
	}

	bool FPSCamera::on_window_resize(const WindowResizeEvent* e) {
		set_perspective(fov, float(e->size.x), float(e->size.y));

		return false;
	}
}