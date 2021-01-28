#pragma once

#include <vector>

#include "../scene/sprite.h"

namespace engine {
	class Layer {
	private:
		TextureBuffer buffer;
		Sprite sprite;
		FrameBufferT frame;

	public:
		Layer();
		virtual ~Layer() {};

		void bind();
		void render();

		virtual void update() = 0;
	};
}