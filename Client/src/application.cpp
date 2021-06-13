#include "application.h"

BlockGameApplication* application = NULL;

BlockGameApplication::BlockGameApplication() : engine::Application("Game"s, { 800, 500 }), log("client.log"s), config("client.json"s) {
    config.get_value("version"s, 1.0);

    reload_resources();

    window.set_title("Game ["s + engine::get_renderer_version().data() + "] ["s + engine::get_adapter_vendor().data() + ' ' + engine::get_video_adapter().data() + ']');
    window.set_icon(texture("icon.png"sv));
}

BlockGameApplication::~BlockGameApplication() {

}

void BlockGameApplication::run() {
    while (running) {
        for (auto& module : modules) {
            module->update();
        }

        update();
    }
}

void BlockGameApplication::reload_resources() {
    resources.flush();

    // Load all resource pack folders

    // Load all mod resource folders

    // Finally load vanilla resources
    resources.load_folder(PROJECT_DIR + "blockgame"s);

    for (auto& [name, file] : resources) {
        const fs::path path = name;

        std::string package = path.begin()->string();

        std::string folder = (++path.begin())->string();

        NameID id = package + ':' + path.stem().string();
    }
}

engine::Program BlockGameApplication::shader(const std::string_view& name) {
    std::string file = ocode::format("%s\\shaders\\%s"sv, "blockgame", name.data());

    return load_shader(file, resources);
}

engine::Texture BlockGameApplication::texture(const std::string_view& name) {
    std::string file = ocode::format("%s\\textures\\%s"sv, "blockgame", name.data());

    return load_texture(file, resources);
}

engine::Font BlockGameApplication::font(const std::string_view& name) {
    std::string file = ocode::format("%s\\fonts\\%s"sv, "blockgame", name.data());

    return load_font(file, resources);
}