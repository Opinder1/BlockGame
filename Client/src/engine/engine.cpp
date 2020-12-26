#include "engine.h"

namespace engine {
    Engine* engine;

    ocode::EventManager* event_manager;

    void init() {
        if (!glfwInit()) {
            throw "Failed to initialise glfw";
        }

        event_manager = new ocode::EventManager();

        engine = new Engine();

        if (glewInit() != GLEW_OK) {
            throw "Failed to initialise glew";
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        engine->window.set_icon(engine::Texture("icon.png"));
    }

    void start(Layer* initial_layer) {
        engine->layers.insert(initial_layer);

        engine->run();

        delete engine;

        delete event_manager;
    }

    Engine::Engine() :
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

        event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Engine::on_window_resize);
        event_manager->EVENT_SUBSCRIBE(engine::WindowCloseEvent, Engine::on_window_close);
    }

    Engine::~Engine() {

    }

    void Engine::run() {
        while (running) {
            update();
        }
    }

    void Engine::update() {
        layers.update();

        window.update();

        glfwPollEvents();
    }

    bool Engine::on_window_resize(const WindowResizeEvent* e) {
        glViewport(0, 0, e->get_width(), e->get_height());
        return false;
    }

    bool Engine::on_window_close(const WindowCloseEvent* e) {
        running = false;

        return false;
    }
}