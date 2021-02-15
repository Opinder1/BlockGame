#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = new ocode::EventManager();

    Application::Application(const std::string& name, glm::uvec2 size) : running(true), window(name, size), surface(window.get_size()) {
        event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Application::on_window_resize);
        event_manager->EVENT_SUBSCRIBE(engine::WindowCloseEvent, Application::on_window_close);
        
        window.set_icon(engine::Texture("icon.png"));

        engine::QuadRenderer::init();
    }

    Application::~Application() {
        engine::QuadRenderer::deinit();

        delete event_manager;
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