#include "window.h"

void on_window_resize(GLFWwindow* window, int event_width, int event_height) {
    ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

    manager->EVENT_POST(WindowResizeEvent, { (uint32)event_width, (uint32)event_height });
}

void on_window_move(GLFWwindow* window, int event_x, int event_y) {
    ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

    manager->EVENT_POST(WindowMoveEvent, { event_x, event_y });
}

void on_window_close(GLFWwindow* window) {
    ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

    manager->EVENT_POST(WindowCloseEvent);
}

void on_window_focus(GLFWwindow* window, int focused) {
    ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

    manager->EVENT_POST(WindowFocusEvent, { (bool)focused });
}

//namespace engine {
    Window::Window(ocode::EventManager* m, const std::string& name, glm::uvec2 size) : ocode::EventDevice(m), window(NULL), last_size(size), last_pos({ 0, 0 }) {
        if (!glfwInit()) {
            error_box("Window Error", "Failed to initialise glfw");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

        window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);

        if (!window) {
            error_box("Window Error", "Failed to create window");
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, m);

        glfwSetWindowSizeLimits(window, size.x, size.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwGetWindowPos(window, &last_pos.x, &last_pos.y);

        glfwSetWindowSizeCallback(window, on_window_resize);
        glfwSetWindowPosCallback(window, on_window_move);
        glfwSetWindowCloseCallback(window, on_window_close);
        glfwSetWindowFocusCallback(window, on_window_focus);
        //glfwSetWindowIconifyCallback();
        //glfwSetWindowMaximizeCallback();
        //glfwSetWindowRefreshCallback();
        //glfwSetFramebufferSizeCallback(this->window, on_framebuffer_resize);

        if (glewInit() != GLEW_OK) {
            error_box("Window Error", "Failed to initialise glew");
            return;
        }
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    bool Window::initialized() {
        return window != NULL;
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

    void Window::set_icon() {
        GLFWimage images[1];

        //images[0] = load_image(file);

        glfwSetWindowIcon(window, 1, images);
    }

    void Window::set_fullscreen(Monitor monitor, bool vsync) {
        this->monitor = monitor;

        if (monitor.is_null()) {
            return;
        }

        monitor.use(window);

        EVENT_POST(WindowResizeEvent, monitor.get_size());
        EVENT_POST(WindowMoveEvent, monitor.get_pos());

        if (vsync) {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }
    }

    void Window::set_windowed() {
        monitor = Monitor();

        glfwSetWindowMonitor(window, nullptr, last_pos.x, last_pos.y, last_size.x, last_size.y, 0);

        EVENT_POST(WindowResizeEvent, last_size);
        EVENT_POST(WindowMoveEvent, last_pos);
    }

    void Window::set_windowed(glm::uvec2 size, glm::ivec2 pos) {
        last_size = size;
        last_pos = pos;

        monitor = Monitor();

        glfwSetWindowMonitor(window, nullptr, pos.x, pos.y, size.x, size.y, 0);

        EVENT_POST(WindowResizeEvent, size);
        EVENT_POST(WindowMoveEvent, pos);
    }

    bool Window::on_monitor_disconnect(const MonitorDisconnectEvent* e) {
        if (!monitor.is_null() && monitor == e->get_monitor()) {
            set_fullscreen(Monitor::get_primary(), true);
        }

        return false;
    }
//}

const glm::uvec2 WindowResizeEvent::get_size() const {
    return event_size;
}

const uint32 WindowResizeEvent::get_width() const {
    return event_size.x;
}

const uint32 WindowResizeEvent::get_height() const {
    return event_size.y;
}

const glm::ivec2 WindowMoveEvent::get_pos() const {
    return event_pos;
}

const int32 WindowMoveEvent::get_x() const {
    return event_pos.x;
}

const int32 WindowMoveEvent::get_y() const {
    return event_pos.y;
}

const bool WindowFocusEvent::get_focused() const {
    return focused;
}