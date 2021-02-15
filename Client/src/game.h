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

	std::vector<Module*> modules;

private:
	void update();

public:
	Game();
	~Game();
};

extern Game* application;