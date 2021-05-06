#include "engine.h"

namespace engine {
    ocode::EventManager* event_manager = NULL;

    Application::Application(const std::string& name, glm::uvec2 size) : events(), running((engine::event_manager = &events, true)), window(name, size), surface(window.get_size()) {
        events.event_subscribe(engine::WindowResizeEvent, on_window_resize);
        events.event_subscribe(engine::WindowCloseEvent, on_window_close);

        reload_resources();
        refresh_resources();
        
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

    void Application::reload_resources() {
        resources.flush();

        resources.load_folder(PROJECT_DIR);
    }

    void Application::refresh_resources() {
        shaders.clear();
        textures.clear();
        materials.clear();
        meshes.clear();

        // This should probably be defined in parent class
        for (auto& item : resources) {
            const fs::path& path = item.first;
            Resource& resource = item.second;

            std::string name, extension;

            for (auto& t : path.parent_path()) {
                name += t.string() + ".";
            }

            name += path.stem().string();
            extension = path.extension().string();

            printf("%s, %s\n", name.c_str(), extension.c_str());

            std::string type = "";  

            if (type == "shaders") {
                if (extension == "vert") shaders.push_back(new Shader(ShaderType::VERTEX, (const char*)resource.data, (uint32)resource.data_size));
                if (extension == "frag") shaders.push_back(new Shader(ShaderType::FRAGMENT, (const char*)resource.data, (uint32)resource.data_size));
                if (extension == "geom") shaders.push_back(new Shader(ShaderType::GEOMETRY, (const char*)resource.data, (uint32)resource.data_size));
                if (extension == "comp") shaders.push_back(new Shader(ShaderType::COMPUTE, (const char*)resource.data, (uint32)resource.data_size));
            }

            if (type == "textures") {
            }

            if (type == "materials") {
            }

            if (type == "meshes") {
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