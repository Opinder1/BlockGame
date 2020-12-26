#pragma once

#include <ocode.h>

#include "shader.h"
#include "material.h"
#include "polygon2d.h"
#include "polygon3d.h"

#include "monitor.h"
#include "window.h"

#include "manager.h"
#include "layer.h"

namespace engine {
	class Engine {
		friend void init();

	public:
		bool running;

		ocode::LogFile log;
		ocode::Config config;

		Window window;
		LayerManager layers;

	private:
		Engine();
		
		void update();

		bool on_window_resize(const WindowResizeEvent* e);
		bool on_window_close(const WindowCloseEvent* e);

	public:
		~Engine();

		void run();
	};

	extern Engine* engine;

	void init();

	void start(Layer* initial_layer);
}