#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "../renderer/framebuffer.h"

namespace engine {
	class Renderer2D {
	public:
		static int camera_buffer_slot;

		static void init();
		static void shutdown();

		static void draw_quad();
	};

	struct Transform2D {
		glm::vec2 position;
	};

	class Scene2D {
	private:
		glm::vec2 size;

		Texture2D texture;
		FrameBuffer frame;

	public:
		Scene2D(glm::vec2 size);
		~Scene2D();

		void use();

		void set_size(const glm::vec2& size);

		glm::vec2 get_size();

		Texture2D get_texture();
	};
}