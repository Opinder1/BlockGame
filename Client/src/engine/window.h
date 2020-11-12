#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "monitor.h"

//namespace engine {
	class Window : ocode::EventDevice {
	private:
		GLFWwindow* window;

		Monitor monitor;

		glm::uvec2 last_size;
		glm::ivec2 last_pos;

	public:
		Window(ocode::EventManager* m, const std::string& name, glm::uvec2 size = { 800, 600 });
		~Window();

		bool initialized();

		void use();
		void update();

		void close();

		void set_icon();

		void set_fullscreen(Monitor monitor, bool vsync);
		void set_windowed();
		void set_windowed(glm::uvec2 size, glm::ivec2 pos);

		bool on_monitor_disconnect(const MonitorDisconnectEvent* e);
	};
//}

class WindowResizeEvent : ocode::Event {
private:
	glm::uvec2 event_size;

public:
	WindowResizeEvent(glm::uvec2 size) : event_size(size) {}

	inline const std::string to_string() const override {
		return std::string("WindowResize: ") + std::to_string(event_size.x) + " " + std::to_string(event_size.y);
	}

	const glm::uvec2 get_size() const;
	const uint32 get_width() const;
	const uint32 get_height() const;
};

class WindowMoveEvent : ocode::Event {
private:
	glm::ivec2 event_pos;

public:
	WindowMoveEvent(glm::ivec2 pos) : event_pos(pos) {}

	inline const std::string to_string() const override {
		return std::string("WindowMove: ") + std::to_string(event_pos.x) + " " + std::to_string(event_pos.y);
	}

	const glm::ivec2 get_pos() const;
	const int32 get_x() const;
	const int32 get_y() const;
};

class WindowCloseEvent : ocode::Event {
public:
	WindowCloseEvent() {}

	inline const std::string to_string() const override {
		return std::string("WindowCloseEvent: ");
	};
};

class WindowFocusEvent : ocode::Event {
private:
	bool focused;

public:
	WindowFocusEvent(bool focused) : focused(focused) {}

	inline const std::string to_string() const override {
		return std::string("WindowFocusEvent: focused: ") + std::to_string(focused);
	};

	const bool get_focused() const;
};