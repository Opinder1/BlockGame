#pragma once

#include <ocode.h>

#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

namespace engine {
	extern ocode::EventManager* event_manager;

	class Monitor {
		friend struct MonitorConnectEvent;
		friend struct MonitorDisconnectEvent;

	private:
		GLFWmonitor* monitor;

		Monitor(GLFWmonitor* monitor) : monitor(monitor) {}

	public:
		Monitor() : monitor(NULL) {}

		bool operator==(Monitor monitor);
		static Monitor init();

		static Monitor get_primary();
		static Monitor get(glm::uint32 id);

		void use(GLFWwindow* window);
		bool is_null();
		const glm::uvec2 get_size();
		const glm::ivec2 get_pos();
	};

	struct MonitorConnectEvent : ocode::Event {
		Monitor monitor;

		MonitorConnectEvent(GLFWmonitor* monitor) : monitor(Monitor(monitor)) {}
	};

	struct MonitorDisconnectEvent : ocode::Event {
		Monitor monitor;

		MonitorDisconnectEvent(GLFWmonitor* monitor) : monitor(Monitor(monitor)) {}
	};
}