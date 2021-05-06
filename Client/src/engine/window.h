#pragma once

#include <ocode.h>

#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include "monitor.h"
#include "renderer/texture.h"

namespace engine {
	extern ocode::EventManager* event_manager;

	class Window {
	private:
		GLFWwindow* window;

		Monitor monitor;

		glm::uvec2 last_size;
		glm::ivec2 last_pos;

	public:
		Window(const Window&) = delete;
		Window(const std::string& name, glm::uvec2 size, bool fullscreen = false);
		~Window();

		void use();
		void update();
		void close();

		void set_icon(const Texture& texture);

		void set_fullscreen(Monitor monitor, bool vsync);
		void set_fullscreen(bool vsync);

		void set_windowed();
		void set_windowed(glm::uvec2 size, glm::ivec2 pos);

		void set_title(const std::string& name);

		void set_mouse_type(int type);

		glm::ivec2 get_size();
		glm::ivec2 get_mouse_pos();
		int get_key(int key);

		void on_monitor_disconnect(const MonitorDisconnectEvent* e);
	};

	struct WindowResizeEvent : ocode::Event {
		glm::uvec2 size;

		WindowResizeEvent(glm::uvec2 size) : size(size) {}
	};

	struct WindowMoveEvent : ocode::Event {
		glm::ivec2 pos;

		WindowMoveEvent(glm::ivec2 pos) : pos(pos) {}
	};

	struct WindowCloseEvent : ocode::Event {

	};

	struct WindowFocusEvent : ocode::Event {
		bool focused;

		WindowFocusEvent(bool focused) : focused(focused) {}
	};

	struct KeyActionEvent : ocode::Event {
		int key, scancode, action, mods;

		KeyActionEvent(int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods) {}
	};

	struct MouseClickEvent : ocode::Event {
		int button, action;
		glm::ivec2 pos;

		MouseClickEvent(int button, int action, glm::ivec2 pos) : button(button), action(action), pos(pos) {}
	};
}