#pragma once

#include <ocode.h>

#include <vector>

#include "scene/scene.h"
#include "scene/mesh.h"
#include "scene/surface.h"
#include "scene/camera.h"

#include "window.h"
#include "monitor.h"

#include "resources.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Application {
	public:
		bool running;

		ocode::EventManager events;

		ResourceManager resources;

		Window window;
		WindowSurface surface;

		std::vector<Shader*> shaders;
		std::vector<Texture*> textures;
		std::vector<Material*> materials;
		std::vector<Mesh*> meshes;

	protected:
		virtual void update() = 0;

		void on_window_resize(const WindowResizeEvent* e);
		void on_window_close(const WindowCloseEvent* e);

	public:
		Application(const std::string& name, glm::uvec2 size);
		~Application();

		void run();

		void reload_resources();
		void refresh_resources();
	};
}