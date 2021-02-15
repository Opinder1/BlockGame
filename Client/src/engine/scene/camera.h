#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "transform.h"
#include "../window.h"
#include "renderer/buffer.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Camera2D : public Transform2D {
	public:
		Camera2D(float width, float height);
		~Camera2D();

		glm::mat2 get_projection();
	};

	class Camera3D : public Transform3D {
	protected:
		glm::mat4 perspective;

		void set_perspective(float fov, glm::vec2 size);

	public:
		Camera3D(float fov, glm::vec2 size);
		~Camera3D();

		virtual glm::vec3 look_direction() = 0;
		virtual glm::vec3 up_direction() = 0;
		virtual glm::vec3 left_direction() = 0;
		
		glm::mat4 get_projection();
	};

	class FPSCamera : public Camera3D {
	private:
		float fov;
		glm::vec2 last_mouse_pos;

	public:
		FPSCamera(float fov, glm::vec2 size);

		void update(glm::vec2 mouse_pos);

		glm::vec3 look_direction() override;
		glm::vec3 up_direction() override;
		glm::vec3 left_direction() override;

	private:
		bool on_window_resize(const WindowResizeEvent* e);
	};
}