#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = NULL;

    Application::Application(const std::string& name, glm::uvec2 size) : events(), running((engine::event_manager = &events, true)), window(name, size), surface(window.get_size()) {
        events.event_subscribe(engine::WindowResizeEvent, on_window_resize);
        events.event_subscribe(engine::WindowCloseEvent, on_window_close);
        
        window.set_icon(engine::Texture("icon.png"));

        engine::QuadRenderer::init();
    }

    Application::~Application() {
        engine::QuadRenderer::deinit();
    }

    void Application::run() {
        while (running) {
            surface.clear();

            update();

            window.update();

            glfwPollEvents();
        }
    }

    void Application::on_window_resize(const WindowResizeEvent* e) {
        surface.resize(e->size);
    }

    void Application::on_window_close(const WindowCloseEvent* e) {
        running = false;
    }
}