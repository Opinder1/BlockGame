#pragma once

#include "engine/engine.h"

class Module {
public:
	virtual void update() = 0;
};

class Application : public engine::Application {
public:
	ocode::LogFile log;
	ocode::Config config;

	std::vector<Module*> modules;

private:
	void update();

public:
	Application();
	~Application();
};

extern Application* application;