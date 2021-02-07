#include "game.h"

Game* application = NULL;

Game::Game() : Application("Game", { 800, 600 }), log("client"), config("client"), texture(window.get_size(), 32), frame(texture), sprite(texture) {
	if (!log.initialized()) {
		throw "Log could not be initialized";
	}

	if (!config.initialized()) {
		throw "Config could not be loaded";
	}

	config.save();

	window.set_title(std::string("Game [") + engine::get_renderer_version() + "] [" + engine::get_adapter_vendor() + " " + engine::get_video_adapter() + "]");

	frame.set_multisample(true);

	window_frame.set_alphatest(true);
}

Game::~Game() {
	config.save();
}

void Game::update() {
	frame.use_cleared();

	for (auto* module : modules) {
		module->update();
	}

    window_frame.use_cleared();

    engine::Sprite::set_material(engine::MSSprite::default_material);

	sprite.set_scale({ 2, 2 });
	sprite.draw();
}

void Game::resize(glm::uvec2 size) {
	frame.resize(size, 32);
}