#pragma once

#include <ocode.h>

#include "../renderer/array.h"

namespace engine {
	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void draw_quad();
	};
}