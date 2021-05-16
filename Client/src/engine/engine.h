#pragma once

#include <ocode.h>

#include <vector>

#include "scene/scene.h"
#include "scene/mesh.h"
#include "scene/surface.h"
#include "scene/camera.h"

#include "window.h"
#include "monitor.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Sound {};

	class Application {
	public:
		bool running;

		ocode::EventManager events;

		Window window;
		WindowSurface surface;

		ocode::ResourceManager resources;

	protected:
		void on_window_resize(const WindowResizeEvent* e);
		void on_window_close(const WindowCloseEvent* e);

		virtual void update() = 0;

	public:
		Application(const std::string& name, glm::uvec2 size);
		~Application();

		virtual void run();

	public:
		Shader load_shader(const rapidjson::Value& data, const std::string& local_path);
		Program load_program(const std::string& name);
	};
}