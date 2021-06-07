#pragma once

#include <ocode.h>

#include "../gl/array.h"

namespace engine {
	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void draw_quad();
	};
}