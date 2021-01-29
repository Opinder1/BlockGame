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
    }

    void start(Layer* initial_layer) {
        application->layers.push_back(initial_layer);

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
            throw "Config could not be loaded";
        }

        if (!window.initialized()) {
            throw "Window failure";
        }

        event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Application::on_window_resize);
        event_manager->EVENT_SUBSCRIBE(engine::WindowCloseEvent, Application::on_window_close);

        config.save();
        
        window.set_icon(engine::Texture("icon.png"));

        gl_init();

        engine::Sprite::init();
    }

    Application::~Application() {
        engine::Sprite::deinit();

        for (auto* layer : layers) {
            delete layer;
        }
    }

    void Application::run() {
        while (running) {
            update();
        }
    }

    void Application::update() {
        for (auto* layer : layers) {
            layer->bind();
            layer->update();
        }

        window.use();

        Sprite::set_material(default_mssprite_material);
        for (auto* layer : layers) {
            layer->render();
        }

        window.update();

        glfwPollEvents();
    }

    bool Application::on_window_resize(const WindowResizeEvent* e) {
        FrameBuffer::use_screen();
        glViewport(0, 0, e->size.x, e->size.y);

        for (auto* layer : layers) {
            layer->resize(e->size);
        }

        return false;
    }

    bool Application::on_window_close(const WindowCloseEvent* e) {
        running = false;

        return false;
    }
}