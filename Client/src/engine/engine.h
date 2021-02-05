#pragma once

#include <ocode.h>

#include "scene/material.h"
#include "scene/mesh.h"
#include "scene/sprite.h"
#include "scene/camera.h"

#include "core/window.h"
#include "core/monitor.h"
#include "core/layer.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Application {
	public:
		bool running;

		Window window;
		FrameBufferS frame;

		std::vector<Layer*> layers;

	protected:
		virtual void update() = 0;

		bool on_window_resize(const WindowResizeEvent* e);
		bool on_window_close(const WindowCloseEvent* e);

	public:
		Application();
		~Application();

		void run();
	};
}