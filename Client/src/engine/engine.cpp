#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = NULL;

    Application::Application() : running(true), window("game"), frame(window.get_size()) {
        event_manager = new ocode::EventManager();

        event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Application::on_window_resize);
        event_manager->EVENT_SUBSCRIBE(engine::WindowCloseEvent, Application::on_window_close);
        
        window.set_icon(engine::Texture("icon.png"));

        engine::Sprite::init();
    }

    Application::~Application() {
        engine::Sprite::deinit();

        delete event_manager;

        for (auto* layer : layers) {
            delete layer;
        }
    }

    void Application::run() {
        while (running) {
            for (auto* layer : layers) {
;               layer->bind();
                layer->update();
            }

            frame.use();

            frame.clear({ 0.0, 0.0, 0.0, 0.0 });
            frame.set_depthtest(false);
            frame.set_alphatest(true);
            frame.set_polymode(PolyMode::Fill);
            frame.set_culling(Culling::Disabled);
            frame.set_multisample(false);

            Sprite::set_material(MSSprite::default_material);
            for (auto* layer : layers) {
                layer->render();
            }

            window.update();

            glfwPollEvents();
        }
    }

    bool Application::on_window_resize(const WindowResizeEvent* e) {
        window.use();

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