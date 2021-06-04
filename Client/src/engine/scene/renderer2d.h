#pragma once

#include <ocode.h>

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
}