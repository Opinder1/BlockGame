#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "monitor.h"
#include "window.h"

#include "layer.h"

#include "camera.h"
#include "shader.h"
#include "material.h"
#include "model.h"

namespace engine {
	void init();

	void start(Layer* initial_layer);

	class Application {
		friend void init();

	public:
		bool running;

		ocode::LogFile log;
		ocode::Config config;

		Window window;
		LayerManager layers;

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