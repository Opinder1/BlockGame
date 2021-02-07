#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = new ocode::EventManager();

    Application::Application(const std::string& name, glm::uvec2 size) : running(true), window(name, size), window_frame(window.get_size()) {
        event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Application::on_window_resize);
        event_manager->EVENT_SUBSCRIBE(engine::WindowCloseEvent, Application::on_window_close);
        
        window.set_icon(engine::Texture("icon.png"));

        engine::Sprite::init();
    }

    Application::~Application() {
        engine::Sprite::deinit();

        delete event_manager;
    }

    void Application::run() {
        while (running) {
            update();

            window.update();

            glfwPollEvents();
        }
    }

    void Application::on_window_resize(const WindowResizeEvent* e) {
        window_frame.resize(e->size);

        resize(e->size);
    }

    void Application::on_window_close(const WindowCloseEvent* e) {
        running = false;
    }
}