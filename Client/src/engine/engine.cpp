#include "engine.h"

engine::Application* application;

namespace engine {

    ocode::EventManager* event_manager;

    void init() {
        if (!glfwInit()) {
            throw "Failed to initialise glfw";
        }

        event_manager = new ocode::EventManager();

        application = new Application();

        application->window.set_icon(engine::Texture("icon.png"));

        gl_init();
    }

    void start(Layer* initial_layer) {
        application->layers.insert(initial_layer);

        application->run();

        delete application;

        delete event_manager;
    }

    Application::Application() :
        running(true),
        log("client"),
        config("client"),
        window("test")
    {
        if (!log.initialized()) {
            throw "Log could not be initialized";
        }

        if (!config.initialized()) {
            log.println("Config could not be loaded\n");
            throw "Config could not be loaded";
        }

        config.save();

        if (!window.initialized()) {
            log.println("Window failure\n");
            throw "Window failure";
        }

        event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Application::on_window_resize);
        event_manager->EVENT_SUBSCRIBE(engine::WindowCloseEvent, Application::on_window_close);
    }

    Application::~Application() {

    }

    void Application::run() {
        while (running) {
            update();
        }
    }

    void Application::update() {
        window.update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        layers.update();

        glfwPollEvents();
    }

    bool Application::on_window_resize(const WindowResizeEvent* e) {
        // Put into some glviewport function
        glViewport(0, 0, e->size.x, e->size.y);

        return false;
    }

    bool Application::on_window_close(const WindowCloseEvent* e) {
        running = false;

        return false;
    }
}