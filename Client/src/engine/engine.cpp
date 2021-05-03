#include "engine.h"

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> out;

    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos)
    {
        end = str.find(delimiter, start);
        out.push_back(str.substr(start, end - start));
    }

    return out;
}

namespace engine {
    ocode::EventManager* event_manager = new ocode::EventManager();

    Application::Application(const std::string& name, glm::uvec2 size) : running(true), window(name, size), surface(window.get_size()) {
        event_manager->event_subscribe(engine::WindowResizeEvent, on_window_resize);
        event_manager->event_subscribe(engine::WindowCloseEvent, on_window_close);

        reload_resources();
        refresh_resources();
        
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

    void Application::reload_resources() {
        resources.flush();

        resources.load_folder(std::string(PROJECT_DIR) + "resources\\");
    }

    void Application::refresh_resources() {
        for (auto it : resources) {
            std::vector<std::string> parts = split(it.first, '\\');

            std::string family = *parts.begin();

            std::string name = *parts.rbegin();

            if (family.compare("shaders") == 0) {
                std::string type = name.substr(name.find('.') + 1, std::string::npos);

                if (type.compare("vert") == 0) shaders.push_back(new Shader(ShaderType::VERTEX, (const char*)it.second.data, (uint32)it.second.data_size));
                if (type.compare("frag") == 0) shaders.push_back(new Shader(ShaderType::FRAGMENT, (const char*)it.second.data, (uint32)it.second.data_size));
                if (type.compare("geom") == 0) shaders.push_back(new Shader(ShaderType::GEOMETRY, (const char*)it.second.data, (uint32)it.second.data_size));
                if (type.compare("comp") == 0) shaders.push_back(new Shader(ShaderType::COMPUTE, (const char*)it.second.data, (uint32)it.second.data_size));
            }
        }
    }

    void Application::on_window_resize(const WindowResizeEvent* e) {
        surface.resize(e->size);
    }

    void Application::on_window_close(const WindowCloseEvent* e) {
        running = false;
    }
}