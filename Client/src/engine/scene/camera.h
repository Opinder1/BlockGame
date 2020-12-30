#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "object.h"
#include "../core/window.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Camera : public Object {
	protected:
		glm::mat4 projection;

		void set_perspective(float fov, float width, float height);

	public:
		Camera(float fov, float width, float height);
		~Camera();

		virtual glm::mat4 get_projection() = 0;
	};

	class FPSCamera : public Camera {
	private:
		float fov;
		glm::vec2 last_mouse_pos;

	public:
		FPSCamera(float fov);

		void update(glm::vec2 mouse_pos);

		glm::vec3 look_direction();
		glm::vec3 up_direction();
		glm::vec3 left_direction();
		glm::mat4 get_projection() override;

	private:
		bool on_window_resize(const WindowResizeEvent* e);
	};
}