#pragma once

#include <ocode.h>

#include "scene/material.h"
#include "scene/mesh.h"
#include "scene/surface.h"
#include "scene/camera.h"

#include "window.h"
#include "monitor.h"

namespace engine {
	// Add to Application class (Unless there is a chance multiple applications could be run which should not be the case)
	extern ocode::EventManager* event_manager;

	class Application {
	public:
		bool running;

		Window window;
		WindowSurface surface;

	protected:
		virtual void update() = 0;

		void on_window_resize(const WindowResizeEvent* e);
		void on_window_close(const WindowCloseEvent* e);

	public:
		Application(const std::string& name, glm::uvec2 size);
		~Application();

		void run();
	};
}