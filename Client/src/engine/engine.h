#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "core/monitor.h"
#include "core/window.h"
#include "core/layer.h"

#include "scene/camera.h"
#include "scene/material.h"
#include "scene/model.h"

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