#include "camera.h"

namespace engine {
	Camera3D::Camera3D(float fov, glm::vec2 size) {
		set_perspective(fov, size);
	}

	Camera3D::~Camera3D() {

	}

	void Camera3D::set_perspective(float fov, glm::vec2 size) {
		//projection = glm::infinitePerspective(fov, width / height, near);
		perspective = glm::perspectiveFov(glm::radians(fov), size.x, size.y, 0.1f, 100000.0f);
	}

	glm::mat4 Camera3D::get_projection() {
		glm::mat4 view = glm::lookAt(
			position,
			position + look_direction(),
			up_direction()
		);
		return perspective * view;
	}

	FPSCamera::FPSCamera(float fov, glm::vec2 size) : Camera3D(fov, size), fov(fov), last_mouse_pos(0, 0) {
		engine::event_manager->event_subscribe(engine::WindowResizeEvent, on_window_resize);
	}

	void FPSCamera::update(glm::vec2 mouse_pos) {
		glm::vec2 rot = mouse_pos - last_mouse_pos;

		rotation.x += (rot.x / 1000.0f);
		rotation.y = glm::clamp(rotation.y - (rot.y / 1000.0f), -1.57f, 1.57f);

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
		set_perspective(fov, glm::vec2(e->size));

		return false;
	}
}