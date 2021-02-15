#include "game.h"

Game* application = NULL;

Game::Game() : Application("Game", { 800, 500 }), log("client"), config("client") {
	if (!log.initialized()) {
		throw "Log could not be initialized";
	}

	if (!config.initialized()) {
		throw "Config could not be loaded";
	}

	config.save();

	window.set_title(std::string("Game [") + engine::get_renderer_version() + "] [" + engine::get_adapter_vendor() + " " + engine::get_video_adapter() + "]");
}

Game::~Game() {
	config.save();

	for (auto* module : modules) {
		delete module;
	}
}

void Game::update() {
	for (auto* module : modules) {
		module->update();
	}
}