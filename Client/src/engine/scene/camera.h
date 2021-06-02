#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "../window.h"
#include "../renderer/buffer.h"

#include "scene.h"

namespace engine {
	extern ocode::EventManager* event_manager;
	
	// TODO Use this to set viewport
	// TOOD Maybe even turn this into a viewport class
	class Camera {
		struct {
			glm::ivec2 pos;
			glm::uvec2 size;
		} viewport;
	};

	class Camera2D : public Transform2D {
	private:
		Scene2D& scene;

		UniformBuffer buffer;

	public:
		Camera2D(Scene2D& scene);
		~Camera2D();

		void use();
	};
}