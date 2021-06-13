#pragma once

#include <ocode.h>

#include "../window.h"
#include "../gl/buffer.h"

#include "scene.h"

namespace engine {
	class Camera {
	private:
		SharedBuffer buffer;

	protected:
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 vp;

	public:
		Camera(const Camera&) = delete;
		Camera();
		~Camera();

		void update();
	};

	class Camera2D : private Camera, public Transform2D {
	private:
		Scene& scene;

		SharedBuffer buffer;

		bool normalized;

	public:
		Camera2D(Scene& scene, bool normalized = true);

		void use();

		void calc_projection();
		void calc_view();
	};

	class PixelCamera2D : public Camera {
	public:
		PixelCamera2D() = default;

		void calc_projection();
	};
}