#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>

#include "renderer2d.h"

namespace engine {
	struct Transform2D {
		glm::vec2 position;
		glm::float32 zoom;
		glm::float32 rotation;
	};

	class Scene2D {
	private:
		glm::vec2 size;

		Texture2D texture;
		FrameBuffer frame;

	public:
		Scene2D(const Scene2D&) = delete;
		Scene2D(glm::vec2 size);
		~Scene2D();

		void use();

		void set_size(const glm::vec2& size);

		glm::vec2 get_size();

		Texture2D get_texture();
	};
}