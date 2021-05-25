#pragma once

#include <ocode.h>

#include <vector>

#include "scene/scene.h"
#include "scene/mesh.h"
#include "scene/surface.h"
#include "scene/camera.h"

#include "resources.h"

#include "window.h"
#include "monitor.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	// TODO implement
	Mesh load_mesh(const std::string& name, const ResourceManager& resources);

	ocode::File read_shader_file(const fs::path& path, const ResourceManager& resources, std::vector<std::string>& visited);
	Program load_program(const std::string& name, const ResourceManager& resources);

	class Application {
	public:
		bool running;

		ocode::EventManager events;

		Window window;
		WindowSurface surface;

		ResourceManager resources;

	protected:
		void on_window_resize(const WindowResizeEvent* e);
		void on_window_close(const WindowCloseEvent* e);

		virtual void update() = 0;

	public:
		Application(const std::string& name, glm::uvec2 size);
		~Application();

		virtual void run();

		Mesh mesh(const std::string& name);
		Program shader(const std::string& name);
		// TODO Add all loading functions
	};
}