#include "camera.h"

namespace engine {
	Camera2D::Camera2D(Scene2D& scene) : scene(scene) {
		buffer._new();

		buffer.create<glm::mat4>(3, nullptr, BufferType::Stream);
	}

	Camera2D::~Camera2D() {
		buffer._delete();
	}

	double x;
	void Camera2D::use() {
		scene.use();
		engine::set_viewport({ 0, 0 }, scene.get_size());
		buffer.activate_slot(Renderer2D::camera_buffer_slot);

		//position = { sin(x) * 10.0, cos(x) * 10.0 };
		x += 0.01;

		glm::mat4 view = {};
		glm::mat4 projection = glm::ortho(0.0f, scene.get_size().x, scene.get_size().y, 0.0f, -1.0f, 1.0f);
		glm::mat4 mp = view * projection;

		buffer.modify(0, 1, &view);
		buffer.modify(1, 1, &projection);
		buffer.modify(2, 1, &mp);
	}
}