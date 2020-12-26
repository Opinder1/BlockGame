#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "manager.h"

namespace engine {
	class Monitor {
		friend class MonitorConnectEvent;
		friend class MonitorDisconnectEvent;

	private:
		GLFWmonitor* monitor;

		Monitor(GLFWmonitor* monitor) : monitor(monitor) {}

	public:
		Monitor() : monitor(NULL) {}

		bool operator==(Monitor monitor);
		static Monitor init();

		static Monitor get_primary();
		static Monitor get(uint32 id);

		void use(GLFWwindow* window);
		bool is_null();
		const glm::uvec2 get_size();
		const glm::ivec2 get_pos();
	};

	class MonitorConnectEvent : ocode::Event {
	private:
		Monitor monitor;

	public:
		MonitorConnectEvent(GLFWmonitor* monitor) : monitor(Monitor(monitor)) {}

		inline const std::string to_string() const override {
			return std::string("MonitorConnect: ") + glfwGetMonitorName(monitor.monitor);
		}

		const Monitor get_monitor() const;
	};

	class MonitorDisconnectEvent : ocode::Event {
	private:
		Monitor monitor;

	public:
		MonitorDisconnectEvent(GLFWmonitor* monitor) : monitor(Monitor(monitor)) {}

		inline const std::string to_string() const override {
			return std::string("MonitorDisconnect: ") + glfwGetMonitorName(monitor.monitor);
		}

		const Monitor get_monitor() const;
	};
}