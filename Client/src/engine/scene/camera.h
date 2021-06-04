#pragma once

#include <ocode.h>

#include "../window.h"
#include "../renderer/buffer.h"

#include "scene.h"

namespace engine {
	class Camera {
	private:
		UniformBuffer buffer;

	protected:
		glm::mat4 projection;
		glm::mat4 view;

	public:
		Camera(const Camera&) = delete;
		Camera();
		~Camera();

		void update();
	};

	class Camera2D : private Camera, public Transform2D {
	private:
		Scene2D& scene;

		UniformBuffer buffer;

		bool normalized;

	protected:
		void calc_projection();
		void calc_view();

	public:
		Camera2D(Scene2D& scene, bool normalized = true);

		void use();

		void set_size(const glm::uvec2& new_size);
	};

	class PixelCamera2D : public Camera {
	public:
		PixelCamera2D() = default;

		void calc_projection();
	};
}