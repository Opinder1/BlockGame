#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = NULL;

    bool config_fullscreen = false;
    bool config_vsync = true;

    Application::Application(const std::string& name, glm::uvec2 size) : events(), running(true), window(name, size) {
        renderer_init();

        Monitor initial_monitor = Monitor::init();

        if (config_fullscreen) {
            window.set_fullscreen(initial_monitor, config_vsync);
        }
        
        engine::event_manager = &events;

        events.event_subscribe(engine::WindowResizeEvent, on_window_resize);
        events.event_subscribe(engine::WindowCloseEvent, on_window_close);

        Renderer2D::init();
    }

    Application::~Application() {
        Renderer2D::shutdown();
    }

    void Application::update() {
        window.update();

        glfwPollEvents();
    }

    void Application::on_window_resize(const WindowResizeEvent* e) {

    }

    void Application::on_window_close(const WindowCloseEvent* e) {
        running = false;
    }
}