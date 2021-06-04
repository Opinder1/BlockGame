#pragma once

#include <ocode.h>

#include <GLFW/glfw3.h>

namespace engine {
	class Monitor {
		friend struct MonitorConnectEvent;
		friend struct MonitorDisconnectEvent;

	private:
		GLFWmonitor* monitor;

		Monitor(GLFWmonitor* monitor) : monitor(monitor) {}

	public:
		static Monitor init();

		Monitor(const Monitor&) = delete;
		Monitor();
		Monitor(glm::uint32 id);

		bool operator==(Monitor monitor);

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