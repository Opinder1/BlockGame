#pragma once

#include <blockgame.h>

#include "engine/engine.h"

class Module {
public:
	virtual void update() = 0;
};

class Game : public engine::Application {
public:
	ocode::LogFile log;
	ocode::Config config;

	engine::MSTextureBuffer texture;
	engine::MSFrameBuffer frame;
	engine::MSSprite sprite;

	std::vector<Module*> modules;

private:
	void update();

	void resize(glm::uvec2 size);

public:
	Game();
	~Game();
};

extern Game* application;