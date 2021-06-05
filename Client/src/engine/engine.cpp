#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = NULL;

    bool config_fullscreen = false;
    bool config_vsync = true;
    
    SettingsBuffer::SettingsBuffer() : time(0), mouse_pos(0) {
        buffer._new();

        buffer.create_data(sizeof(time) + sizeof(mouse_pos), nullptr, BufferType::Stream);
    }

    SettingsBuffer::~SettingsBuffer() {
        buffer._delete();
    }

    void SettingsBuffer::update() {
        buffer.activate_slot(0);

        buffer.modify_data(0, sizeof(time), &time);
        buffer.modify_data(sizeof(time), sizeof(mouse_pos), &mouse_pos);
    }

    Application::Application(const std::string& name, glm::uvec2 size) : running(true), events(), window(name, size) {
        renderer_init();

        Monitor initial_monitor = Monitor::init();

        if (config_fullscreen) {
            window.set_fullscreen(initial_monitor, config_vsync);
        }

        Renderer2D::init();
        
        engine::event_manager = &events;

        events.event_subscribe(engine::WindowResizeEvent, on_window_resize);
        events.event_subscribe(engine::WindowCloseEvent, on_window_close);
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