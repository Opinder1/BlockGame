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

    for (auto& [name, resource] : resources) {
        const fs::path& path = name;

        std::string directory = path.lexically_relative(*path.begin()).parent_path().u8string() + '\\';

        NameID id = path.begin()->u8string() + ':' + path.stem().u8string();

        std::string extension = path.extension().u8string();

        printf("%s %i\n", name.c_str(), name.size());
    }

    try {
        load_shader("blockgame\\shaders\\sprite\\sprite.json");
    }
    catch (engine::program_exception& e) {
        printf("[%s] %s\n", "blockgame\\shaders\\sprite\\sprite.json", e.message.c_str());
    }
}