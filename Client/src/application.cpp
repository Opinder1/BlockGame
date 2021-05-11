#include "application.h"

BlockGameApplication* application = NULL;

std::string BlockGameApplication::base_name = "base";

BlockGameApplication::BlockGameApplication() : engine::Application("Game", { 800, 500 }), log("client"), config("client") {
	if (!log.initialized()) {
		throw "Log could not be initialized";
	}

	config.get_value("version", 1.0);

	window.set_title(std::string("Game [") + engine::get_renderer_version() + "] [" + engine::get_adapter_vendor() + " " + engine::get_video_adapter() + "]");

    reload_resources();
    refresh_resources();
}

BlockGameApplication::~BlockGameApplication() {

}

void BlockGameApplication::run() {
    engine::Application::run();
}

void BlockGameApplication::update() {
	for (auto& module : modules) {
		module->update();
	}
}

void BlockGameApplication::reload_resources() {
    resources.flush();

    // Load all resource pack folders

    // Load all mod resource folders

    // Finally load vanilla resources
    resources.load_folder(PROJECT_DIR);
}

void BlockGameApplication::refresh_resources() {
    engine::Application::reset();

    for (auto& item : resources) {
        const fs::path& path = item.first;
        Resource& resource = item.second;

        NameID name = path.begin()->string() + ":" + path.stem().string();

        std::string spec_path = path.lexically_relative(*path.begin()).parent_path().string() + "\\" + path.begin()->string() + ":" + path.stem().string();

        std::string extension = path.extension().string();

        if (extension == "vert") shaders.push_back(new engine::Shader(engine::ShaderType::VERTEX, (const char*)resource.data, (uint32)resource.data_size));
        if (extension == "frag") shaders.push_back(new engine::Shader(engine::ShaderType::FRAGMENT, (const char*)resource.data, (uint32)resource.data_size));
        if (extension == "geom") shaders.push_back(new engine::Shader(engine::ShaderType::GEOMETRY, (const char*)resource.data, (uint32)resource.data_size));
        if (extension == "comp") shaders.push_back(new engine::Shader(engine::ShaderType::COMPUTE, (const char*)resource.data, (uint32)resource.data_size));
    }
}