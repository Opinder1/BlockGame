#pragma once

#include "ocode.h"

#include <GLFW/glfw3.h>

#include "monitor.h"

struct WindowSize {
	uint32 width;
	uint32 height;
};

struct WindowPos {
	int32 x;
	int32 y;
};

class Window : ocode::EventDevice {
private:
	GLFWwindow* window;

	Monitor monitor;

	WindowSize last_size;
	WindowPos last_pos;

public:
	Window(ocode::EventManager* m, const std::string& name, WindowSize size = { 800, 600 });
	~Window();

	bool initialized();

	void update();

	void close();

	void set_icon();

	void set_fullscreen(Monitor monitor, bool vsync);
	void set_windowed();
	void set_windowed(WindowSize size, WindowPos pos);

	bool on_monitor_disconnect(const MonitorDisconnectEvent* e);
};

class WindowResizeEvent : ocode::Event {
private:
	WindowSize event_size;

public:
	WindowResizeEvent(WindowSize size) : event_size(size) {}

	const std::string to_string() const override;

	const WindowSize get_size() const;
	const uint32 get_width() const;
	const uint32 get_height() const;
};

class WindowMoveEvent : ocode::Event {
private:
	WindowPos event_pos;

public:
	WindowMoveEvent(WindowPos pos) : event_pos(pos) {}

	const std::string to_string() const override;

	const WindowPos get_pos() const;
	const int32 get_x() const;
	const int32 get_y() const;
};