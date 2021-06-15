#include "window.h"

namespace engine {
    extern ocode::EventManager* event_manager;

    glm::ivec2 get_cursor_pos_rel(GLFWwindow* window) {
        glm::dvec2 pos;
        glfwGetCursorPos(window, &pos.x, &pos.y);

        int height;
        glfwGetWindowSize(window, NULL, &height);

        return glm::ivec2(pos.x, height - pos.y);
    }

    void glfw_init() {
        if (!glfwInit()) throw window_exception{ "Failed to initialise glfw"sv };

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    }

    void on_window_resize(GLFWwindow* window, int event_width, int event_height) {
        event_manager->event_post(WindowResizeEvent, { event_width, event_height });
    }

    void on_window_move(GLFWwindow* window, int event_x, int event_y) {
        event_manager->event_post(WindowMoveEvent, { event_x, event_y });
    }

    void on_window_close(GLFWwindow* window) {
        event_manager->event_post(WindowCloseEvent);
    }

    void on_window_focus(GLFWwindow* window, int focused) {
        event_manager->event_post(WindowFocusEvent, focused);
    }

    void on_key_action(GLFWwindow* window, int key, int scancode, int action, int mods) {
        event_manager->event_post(KeyActionEvent, key, scancode, action, mods);
    }

    void on_mouse_click(GLFWwindow* window, int button, int action, int mods) {
        event_manager->event_post(MouseClickEvent, button, action, get_cursor_pos_rel(window));
    }

    Window::Window(const std::string& name, glm::uvec2 size) : window(NULL), last_size(size), last_pos({ 0, 0 }) {
        glfw_init();

        window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);

        if (!window) throw window_exception{ "Failed to initialise window"sv };

        use();
        last_pos = get_pos();
        set_limits(size, { GLFW_DONT_CARE, GLFW_DONT_CARE });

        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }

        glfwSetWindowSizeCallback(window, on_window_resize);
        glfwSetWindowPosCallback(window, on_window_move);
        glfwSetWindowCloseCallback(window, on_window_close);
        glfwSetWindowFocusCallback(window, on_window_focus);
        //glfwSetWindowIconifyCallback();
        //glfwSetWindowMaximizeCallback();
        //glfwSetWindowRefreshCallback();
        //glfwSetFramebufferSizeCallback();
        glfwSetKeyCallback(window, on_key_action);
        glfwSetMouseButtonCallback(window, on_mouse_click);
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    void Window::use() {
        glfwMakeContextCurrent(window);

        surface.clear();

        set_viewport({ 0, 0 }, get_size());
    }

    void Window::update() {
        glfwSwapBuffers(window);
    }

    void Window::close() {
        glfwSetWindowShouldClose(window, true);
    }

    void Window::set_fullscreen(Monitor& monitor, bool vsync) {
        if (monitor.is_null()) throw window_exception{ "Invalid monitor for fullscreen"sv };

        monitor.use(window);

        event_manager->event_post(WindowResizeEvent, monitor.get_size());
        event_manager->event_post(WindowMoveEvent, monitor.get_pos());

        if (vsync) {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }
    }

    void Window::set_windowed() {
        glfwSetWindowMonitor(window, nullptr, last_pos.x, last_pos.y, last_size.x, last_size.y, 0);
    }

    void Window::set_windowed(glm::uvec2 size, glm::ivec2 pos) {
        last_size = size;
        last_pos = pos;

        glfwSetWindowMonitor(window, nullptr, pos.x, pos.y, size.x, size.y, 0);
    }

    void Window::set_icon(Texture texture) {
        glm::ivec2 size = texture->get_size();

        GLFWimage image = { size.x, size.y, texture->get_data() };

        glfwSetWindowIcon(window, 1, &image);
    }

    void Window::set_title(const std::string& name) {
        glfwSetWindowTitle(window, name.c_str());
    }

    void Window::set_limits(const glm::ivec2 min, const glm::ivec2 max) {
        glfwSetWindowSizeLimits(window, min.x, min.y, max.x, max.y);
    }

    void Window::set_mouse_type(int type) {
        glfwSetInputMode(window, GLFW_CURSOR, type);
    }

    glm::ivec2 Window::get_pos() {
        glm::ivec2 pos;
        glfwGetWindowPos(window, &pos.x, &pos.y);
        return pos;
    }

    glm::uvec2 Window::get_size() {
        glm::ivec2 size;
        glfwGetWindowSize(window, &size.x, &size.y);
        return size;
    }

    glm::ivec2 Window::get_mouse_pos() {
        return get_cursor_pos_rel(window);
    }

    int Window::get_key(int key) {
        return glfwGetKey(window, key);
    }
}