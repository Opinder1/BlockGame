#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = NULL;

    bool config_fullscreen = false;
    bool config_vsync = true;

    Application::Application(const std::string& name, glm::uvec2 size) : events(), running(true), window(name, size) {
        // TODO constructor used to have: , surface(window.get_size())
        if (!renderer_init()) {
            // TODO make this not a c string
            throw "Failed to initialise renderer";
        }
        
        engine::event_manager = &events;

        events.event_subscribe(engine::WindowResizeEvent, on_window_resize);
        events.event_subscribe(engine::WindowCloseEvent, on_window_close);

        Monitor monitor = Monitor::init();

        if (config_fullscreen) {
            window.set_fullscreen(monitor, config_vsync);
        }
        
        window.set_icon(engine::Texture("blockgame\\textures\\icon.png"s));

        Renderer2D::init();
    }

    Application::~Application() {
        Renderer2D::shutdown();
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

    }

    void Application::on_window_close(const WindowCloseEvent* e) {
        running = false;
    }

    Program Application::shader(const std::string& name) {
        return load_program(name, resources);
    }
}