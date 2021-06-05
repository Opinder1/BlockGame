#pragma once

#include <ocode.h>

#include <vector>

#include "scene/scene.h"
#include "scene/camera.h"

#include "resources/resources.h"

#include "window.h"
#include "monitor.h"

namespace engine {
	class SettingsBuffer {
	private:
		SharedBuffer buffer;

	protected:
		glm::float64 time;
		glm::float64 delta_time;
		glm::uint64 frame;
		glm::uvec2 window_size;
		glm::ivec2 mouse_pos;

		SettingsBuffer();
		~SettingsBuffer();

		void update();
	};

	class Application {
	public:
		bool running;

		ocode::EventManager events;

		ResourceManager resources;

		Window window;

	protected:
		void on_window_resize(const WindowResizeEvent* e);
		void on_window_close(const WindowCloseEvent* e);

		void update();

	public:
		Application(const Application&) = delete;
		Application(const std::string& name, glm::uvec2 size);
		~Application();
	};
}