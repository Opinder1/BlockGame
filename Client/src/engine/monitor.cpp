#include "monitor.h"

namespace engine {
    ocode::EventManager* Monitor::manager = NULL;

    bool Monitor::operator==(Monitor monitor) {
        return this->monitor == monitor.monitor;
    }

    void on_monitor_change(GLFWmonitor* monitor, int event) {
        if (event == GLFW_CONNECTED) {
            Monitor::manager->event_post<MonitorConnectEvent>(new MonitorConnectEvent(monitor));
        }
        else if (event == GLFW_DISCONNECTED) {
            Monitor::manager->event_post<MonitorDisconnectEvent>(new MonitorDisconnectEvent(monitor));
        }
    }

    Monitor Monitor::init(ocode::EventManager* m) {
        glfwSetMonitorCallback(on_monitor_change);

        Monitor::manager = m;

        return Monitor::get_primary();
    }

    Monitor Monitor::get_primary() {
        return Monitor(glfwGetPrimaryMonitor());
    }

    Monitor Monitor::get(uint32 id) {
        uint32 count;

        GLFWmonitor** monitor_list = glfwGetMonitors((int32*)&count);

        if (id > count) {
            id = count;
        }

        return Monitor(monitor_list[id]);
    }

    void Monitor::use(GLFWwindow* window) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    bool Monitor::is_null() {
        return monitor == NULL;
    }

    const glm::uvec2 Monitor::get_size() {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        return { (uint32)mode->width, (uint32)mode->height };
    }

    const glm::ivec2 Monitor::get_pos() {
        glm::ivec2 pos;

        glfwGetMonitorWorkarea(monitor, &pos.x, &pos.y, nullptr, nullptr);

        return pos;
    }

    const Monitor MonitorConnectEvent::get_monitor() const {
        return monitor;
    }

    const Monitor MonitorDisconnectEvent::get_monitor() const {
        return monitor;
    }
}