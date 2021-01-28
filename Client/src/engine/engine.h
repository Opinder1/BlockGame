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

	void init();

	void start(Layer* initial_layer);

	class Application {
		friend void init();

	public:
		bool running;

		ocode::LogFile log;
		ocode::Config config;

		Window window;
		std::vector<Layer*> layers;

	private:
		Application();
		
		void update();

		bool on_window_resize(const WindowResizeEvent* e);
		bool on_window_close(const WindowCloseEvent* e);

	public:
		~Application();

		void run();
	};

}

extern engine::Application* application;