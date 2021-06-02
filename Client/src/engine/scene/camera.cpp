#include "camera.h"

namespace engine {
	Camera2D::Camera2D(Scene2D& scene) : scene(scene) {

	}

	Camera2D::~Camera2D() {

	}

	void Camera2D::use() {
		scene.use();
		engine::set_viewport({ 0, 0 }, scene.get_size());
		buffer.activate_slot(Renderer2D::camera_buffer_slot);

		// TODO Set camera buffer to use camera transform
	}
}