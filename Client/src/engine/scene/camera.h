#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "../window.h"
#include "../renderer/buffer.h"

#include "scene.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Camera2D : public Transform2D {
	private:
		Scene2D& scene;

		UniformBuffer buffer;

	public:
		Camera2D(const Camera2D&) = delete;
		Camera2D(Scene2D& scene);
		~Camera2D();

		void use();
	};
}