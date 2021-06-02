#include "application.h"

BlockGameApplication* application = NULL;

std::string BlockGameApplication::base_name = "base"s;

BlockGameApplication::BlockGameApplication() : engine::Application("Game"s, { 800, 500 }), log("client.log"s), config("client.json"s) {
    config.get_value("version"s, 1.0);

    window.set_title("Game ["s + engine::get_renderer_version().data() + "] ["s + engine::get_adapter_vendor().data() + ' ' + engine::get_video_adapter().data() + ']');

    reload_resources();
}

BlockGameApplication::~BlockGameApplication() {

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

    for (auto& [name, file] : resources) {
        const fs::path path = name;

        std::string package = path.begin()->string();

        std::string folder = (++path.begin())->string();

        NameID id = package + ':' + path.stem().string();
    }
}