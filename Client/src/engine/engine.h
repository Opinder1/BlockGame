#pragma once

#include <ocode.h>

#include <vector>

#include "scene/scene.h"
#include "scene/camera.h"

#include "resources/resources.h"

#include "window.h"
#include "monitor.h"

namespace engine {
	class Settings {
		glm::float64 time;
		UniformBuffer buffer;

		Settings();
		~Settings();
	};

	class Application {
	private:

	public:
		bool running;

		ocode::EventManager events;

		ResourceManager resources;

		Window window;

	protected:
		void on_window_resize(const WindowResizeEvent* e);
		void on_window_close(const WindowCloseEvent* e);

		virtual void update() = 0;

	public:
		Application(const Application&) = delete;
		Application(const std::string& name, glm::uvec2 size);
		~Application();

		void run();

		// TODO remove these
		Program shader(const std::string& name);
		Texture texture(const std::string& name);

	};
}