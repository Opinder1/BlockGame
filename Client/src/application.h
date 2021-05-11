#pragma once

#include <blockgame.h>

#include "engine/engine.h"

#include "resources.h"

class Module {
public:
	virtual void update() = 0;
};

class BlockGameApplication : public engine::Application {
public:
	static std::string base_name;

	ocode::LogFile log;
	ocode::Config config;

	ResourceManager resources;

	std::vector<std::unique_ptr<Module>> modules;

private:
	void update() override;

	void reload_resources();
	void refresh_resources();

public:
	BlockGameApplication();
	~BlockGameApplication();

	void run() override;
};

extern BlockGameApplication* application;