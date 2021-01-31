#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "transform.h"
#include "../core/window.h"
#include "../renderer/buffer.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Camera : public Transform3D {
	protected:
		glm::mat4 projection;

		void set_perspective(float fov, float width, float height);

	public:
		Camera(float fov, float width, float height);
		~Camera();

		virtual glm::vec3 look_direction() = 0;
		virtual glm::vec3 up_direction() = 0;
		virtual glm::vec3 left_direction() = 0;

		glm::mat4 get_projection();
	};

	class FPSCamera : public Camera {
	private:
		float fov;
		glm::vec2 last_mouse_pos;

	public:
		FPSCamera(float fov);

		void update(glm::vec2 mouse_pos);

		glm::vec3 look_direction() override;
		glm::vec3 up_direction() override;
		glm::vec3 left_direction() override;

	private:
		bool on_window_resize(const WindowResizeEvent* e);
	};

	class SpaceCamera : public Camera {
	
	};
}