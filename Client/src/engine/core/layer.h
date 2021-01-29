#pragma once

#include <vector>

#include "../scene/sprite.h"

namespace engine {
	class Layer {
	private:
		MSTextureBuffer texture;
		MSSprite sprite;
		FrameBufferM frame;

	public:
		Layer();
		virtual ~Layer() {};

		void resize(glm::uvec2 size);
		void bind();
		void render();

		virtual void update() = 0;
	};
}