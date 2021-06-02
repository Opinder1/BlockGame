#pragma once

#include <blockgame.h>

#include "engine/engine.h"

class Module {
public:
	virtual void update() = 0;
};

class BlockGameApplication : public engine::Application {
public:
	static std::string_view base_name;

	ocode::LogFile log;
	ocode::Config config;

	std::vector<std::unique_ptr<Module>> modules;

private:
	void update() override;

	void reload_resources();

public:
	BlockGameApplication();
	~BlockGameApplication();
};

extern BlockGameApplication* application;