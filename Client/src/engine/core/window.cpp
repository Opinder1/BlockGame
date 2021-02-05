#include "window.h"

namespace engine {
    void on_window_resize(GLFWwindow* window, int event_width, int event_height) {
        event_manager->EVENT_POST(WindowResizeEvent, { event_width, event_height });
    }

    void on_window_move(GLFWwindow* window, int event_x, int event_y) {
        event_manager->EVENT_POST(WindowMoveEvent, { event_x, event_y });
    }

    void on_window_close(GLFWwindow* window) {
        event_manager->EVENT_POST(WindowCloseEvent);
    }

    void on_window_focus(GLFWwindow* window, int focused) {
        event_manager->EVENT_POST(WindowFocusEvent, focused);
    }

    void on_key_action(GLFWwindow* window, int key, int scancode, int action, int mods) {
        event_manager->EVENT_POST(KeyActionEvent, key, scancode, action, mods);
    }

    Window::Window(const std::string& name, glm::uvec2 size) : window(NULL), last_size({ 0, 0 }), last_pos({ 0, 0 }) {
        if (!glfwInit()) {
            throw "Failed to initialise glfw";
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

        window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);

        if (!window) {
            throw "Failed to initialise window";
        }

        last_size = size;
        last_pos = { 0, 0 };

        glfwMakeContextCurrent(window);
        //glfwSetWindowUserPointer(window, manager);

        glfwSetWindowSizeLimits(window, size.x, size.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwGetWindowPos(window, &last_pos.x, &last_pos.y);

        glfwSetWindowSizeCallback(window, on_window_resize);
        glfwSetWindowPosCallback(window, on_window_move);
        glfwSetWindowCloseCallback(window, on_window_close);
        glfwSetWindowFocusCallback(window, on_window_focus);
        //glfwSetWindowIconifyCallback();
        //glfwSetWindowMaximizeCallback();
        //glfwSetWindowRefreshCallback();
        //glfwSetFramebufferSizeCallback();

        glfwSetKeyCallback(window, on_key_action);

        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }

        if (!renderer_init()) {
            throw "Failed to initialise renderer";
        }
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    void Window::use() {
        //glfwMakeContextCurrent(window);
    }

    void Window::update() {
        glfwSwapBuffers(window);
    }

    void Window::close() {
        glfwSetWindowShouldClose(window, true);
    }

    void Window::set_icon(const Texture& texture) {
        glm::ivec2 size = texture.get_size();

        GLFWimage image = { size.x, size.y, (uint8*)texture.get_data() };

        glfwSetWindowIcon(window, 1, &image);
    }

    void Window::set_fullscreen(Monitor monitor, bool vsync) {
        this->monitor = monitor;

        if (monitor.is_null()) {
            return;
        }

        monitor.use(window);

        event_manager->EVENT_POST(WindowResizeEvent, monitor.get_size());
        event_manager->EVENT_POST(WindowMoveEvent, monitor.get_pos());

        if (vsync) {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }
    }

    void Window::set_fullscreen(bool vsync) {
        set_fullscreen(Monitor::get_primary(), vsync);
    }

    void Window::set_windowed() {
        monitor = Monitor();

        glfwSetWindowMonitor(window, nullptr, last_pos.x, last_pos.y, last_size.x, last_size.y, 0);

        event_manager->EVENT_POST(WindowResizeEvent, last_size);
        event_manager->EVENT_POST(WindowMoveEvent, last_pos);
    }

    void Window::set_windowed(glm::uvec2 size, glm::ivec2 pos) {
        last_size = size;
        last_pos = pos;

        monitor = Monitor();

        glfwSetWindowMonitor(window, nullptr, pos.x, pos.y, size.x, size.y, 0);

        event_manager->EVENT_POST(WindowResizeEvent, size);
        event_manager->EVENT_POST(WindowMoveEvent, pos);
    }

    void Window::set_mouse_type(int type) {
        glfwSetInputMode(window, GLFW_CURSOR, type);
    }

    glm::ivec2 Window::get_size() {
        glm::ivec2 size;
        glfwGetWindowSize(window, &size.x, &size.y);
        return size;
    }

    glm::vec2 Window::get_mouse_pos() {
        glm::dvec2 size;
        glfwGetCursorPos(window, &size.x, &size.y);
        return size;
    }

    int Window::get_key(int key) {
        return glfwGetKey(window, key);
    }

    bool Window::on_monitor_disconnect(const MonitorDisconnectEvent* e) {
        if (!monitor.is_null() && monitor == e->monitor) {
            set_fullscreen(Monitor::get_primary(), true);
        }

        return false;
    }
}