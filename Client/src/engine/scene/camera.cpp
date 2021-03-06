#include "camera.h"

namespace engine {
	Camera::Camera() : projection(1), view(1), vp(1) {
		buffer._new();

		buffer.create<glm::mat4>(3, nullptr, BufferType::Stream);
	}

	Camera::~Camera() {
		buffer._delete();
	}

	void Camera::update() {
		buffer.activate_slot(1);

		vp = projection * view;

		buffer.modify(0, 1, &view);
		buffer.modify(1, 1, &projection);
		buffer.modify(2, 1, &vp);
	}

	Camera2D::Camera2D(Scene& scene, bool normalized) : scene(scene), normalized(normalized) {
		calc_projection();
	}

	void Camera2D::use() {
		calc_view();

		update();

		scene.use();
		set_viewport({ 0, 0 }, scene.get_size());
	}

	void Camera2D::calc_projection() {
		glm::vec2 size = scene.get_size() / 2;
		if (normalized) size = { 1, size.y / size.x };
		projection = glm::ortho(-size.x, size.x, -size.y, size.y);
	}

	void Camera2D::calc_view() {
		view = glm::scale(glm::vec3(scale, 1));
		view = glm::rotate(view, rotation, glm::vec3(0, 0, 1));
		view = glm::translate(view, glm::vec3(position, 0));
	}
}