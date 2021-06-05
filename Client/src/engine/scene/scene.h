#pragma once

#include <ocode.h>

#include "../renderer/frame_buffer.h"

#include "renderer2d.h"

namespace engine {
	struct Transform2D {
		glm::vec2 position = { 0, 0 };
		glm::float32 rotation = 0;
		glm::vec2 scale = { 1, 1 };

		glm::mat4 get_transform();
	};

	class Scene2D {
	private:
		glm::uvec2 size;

		Texture2D texture;
		FrameBuffer frame;

	public:
		Scene2D(const Scene2D&) = delete;
		Scene2D(glm::uvec2 size);
		~Scene2D();

		void use();

		void set_size(const glm::uvec2& size);

		glm::uvec2 get_size();

		Texture2D get_texture();
	};
}