#include "application.h"

Application* application = NULL;

std::string Application::base_name = "base";

Application::Application() : engine::Application("Game", { 800, 500 }), log("client"), config("client") {
	if (!log.initialized()) {
		throw "Log could not be initialized";
	}

	config.get_value("version", 1.0);

	window.set_title(std::string("Game [") + engine::get_renderer_version() + "] [" + engine::get_adapter_vendor() + " " + engine::get_video_adapter() + "]");
}

Application::~Application() {

}

void Application::update() {
	for (auto& module : modules) {
		module->update();
	}
}