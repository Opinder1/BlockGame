#pragma once

#include "engine/engine.h"

class Module {
public:
	virtual void update() = 0;
};

class Application : public engine::Application {
public:
	static std::string base_name;

	ocode::LogFile log;
	ocode::Config config;

	std::vector<std::unique_ptr<Module>> modules;

private:
	void update() override;

public:
	Application();
	~Application();
};

extern Application* application;