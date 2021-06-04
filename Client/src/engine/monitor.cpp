#include "monitor.h"

namespace engine {
    extern ocode::EventManager* event_manager;

    bool Monitor::operator==(Monitor monitor) {
        return this->monitor == monitor.monitor;
    }

    void on_monitor_change(GLFWmonitor* monitor, int event) {
        if (event == GLFW_CONNECTED) {
            event_manager->event_post(MonitorConnectEvent, monitor);
        }
        else if (event == GLFW_DISCONNECTED) {
            event_manager->event_post(MonitorDisconnectEvent, monitor);
        }
    }

    Monitor Monitor::init() {
        glfwSetMonitorCallback(on_monitor_change);

        return Monitor();
    }

    Monitor::Monitor() : monitor(glfwGetPrimaryMonitor()) {

    }

    Monitor::Monitor(glm::uint32 id) : monitor(nullptr) {
        glm::uint32 count;

        GLFWmonitor** monitor_list = glfwGetMonitors((int*)&count);

        if (monitor_list) monitor = monitor_list[id > count ? count : id];
    }

    void Monitor::use(GLFWwindow* window) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

        // TODO hmm maybe people dont want to run at their monitors refresh rate as it could be glitched or something
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    bool Monitor::is_null() {
        return monitor == nullptr;
    }

    const glm::uvec2 Monitor::get_size() {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        return { (glm::uint32)mode->width, (glm::uint32)mode->height };
    }

    const glm::ivec2 Monitor::get_pos() {
        glm::ivec2 pos;

        glfwGetMonitorWorkarea(monitor, &pos.x, &pos.y, nullptr, nullptr);

        return pos;
    }
}