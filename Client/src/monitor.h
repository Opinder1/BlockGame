#pragma once

#include "ocode.h"

#include <GLFW/glfw3.h>

struct MonitorSize {
	uint32 width;
	uint32 height;
};

struct MonitorPos {
	int32 x;
	int32 y;
};

class Monitor {
	friend class MonitorConnectEvent;
	friend class MonitorDisconnectEvent;

private:
	GLFWmonitor* monitor;

	Monitor(GLFWmonitor* monitor) : monitor(monitor) {}

public:
	Monitor() : monitor(NULL) {}

	bool operator==(Monitor monitor);

	static ocode::EventManager* manager;
	static Monitor init(ocode::EventManager* manager);

	static Monitor get_primary();
	static Monitor get(uint32 id);

	void use(GLFWwindow* window);

	bool is_null();
	const MonitorSize get_size();
	const MonitorPos get_pos();
};

class MonitorConnectEvent : ocode::Event {
private:
	Monitor monitor;

public:
	MonitorConnectEvent(GLFWmonitor* monitor) : monitor(Monitor(monitor)) {}

	const std::string to_string() const override;

	const Monitor get_monitor() const;
};

class MonitorDisconnectEvent : ocode::Event {
private:
	Monitor monitor;

public:
	MonitorDisconnectEvent(GLFWmonitor* monitor) : monitor(Monitor(monitor)) {}

	const std::string to_string() const override;

	const Monitor get_monitor() const;
};