#include "window.h"

void on_window_resize(GLFWwindow* window, int event_width, int event_height) {
    ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

    manager->EVENT_POST(WindowResizeEvent, { (uint32)event_width, (uint32)event_height });
}

void on_window_move(GLFWwindow* window, int event_x, int event_y) {
    ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

    manager->EVENT_POST(WindowMoveEvent, { event_x, event_y });
}

Window::Window(ocode::EventManager* m, const std::string& name, WindowSize size) : ocode::EventDevice(m), window(NULL), last_size(size), last_pos({ 0, 0 }) {
    if (!glfwInit()) {
        error_box("Window Error", "Failed to initialise glfw");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow(size.width, size.height, name.c_str(), nullptr, nullptr);

    if (!window) {
        error_box("Window Error", "Failed to create window");
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, m);

    glfwSetWindowSizeLimits(window, size.width, size.height, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwGetWindowPos(window, &last_pos.x, &last_pos.y);

    glfwSetWindowSizeCallback(window, on_window_resize);
    glfwSetWindowPosCallback(window, on_window_move);
    //glfwSetFramebufferSizeCallback(this->window, on_framebuffer_resize);
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::set_fullscreen(Monitor monitor, bool vsync) {
    this->monitor = monitor;

    if (monitor.is_null()) {
        return;
    }

    monitor.use(window);

    EVENT_POST(WindowResizeEvent, (WindowSize&)monitor.get_size());
    EVENT_POST(WindowMoveEvent, (WindowPos&)monitor.get_pos());

    if (vsync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}

void Window::set_windowed() {
    monitor = Monitor();

    glfwSetWindowMonitor(window, nullptr, last_pos.x, last_pos.y, last_size.width, last_size.height, 0);

    EVENT_POST(WindowResizeEvent, last_size);
    EVENT_POST(WindowMoveEvent, last_pos);
}

void Window::set_windowed(WindowSize size, WindowPos pos) {
    last_size = size;
    last_pos = pos;

    monitor = Monitor();

    glfwSetWindowMonitor(window, nullptr, pos.x, pos.y, size.width, size.height, 0);

    EVENT_POST(WindowResizeEvent, size);
    EVENT_POST(WindowMoveEvent, pos);
}

bool Window::initialized() {
    return window != NULL;
}

void Window::update() {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::close() {
    glfwSetWindowShouldClose(window, true);
}

void Window::set_icon() {
    GLFWimage images[1];

    //images[0] = load_image(file);

    glfwSetWindowIcon(window, 1, images);
}

bool Window::on_monitor_disconnect(const MonitorDisconnectEvent* e) {
    if (!monitor.is_null() && monitor == e->get_monitor()) {
        set_fullscreen(Monitor::get_primary(), true);
    }

    return false;
}

const std::string WindowResizeEvent::to_string() const {
    return std::string("WindowResize: ") + std::to_string(event_size.width) + " " + std::to_string(event_size.height);
}

const WindowSize WindowResizeEvent::get_size() const {
    return event_size;
}

const uint32 WindowResizeEvent::get_width() const {
    return event_size.width;
}

const uint32 WindowResizeEvent::get_height() const {
    return event_size.height;
}

const std::string WindowMoveEvent::to_string() const {
    return std::string("WindowMove: ") + std::to_string(event_pos.x) + " " + std::to_string(event_pos.y);
}

const WindowPos WindowMoveEvent::get_pos() const {
    return event_pos;
}

const int32 WindowMoveEvent::get_x() const {
    return event_pos.x;
}

const int32 WindowMoveEvent::get_y() const {
    return event_pos.y;
}