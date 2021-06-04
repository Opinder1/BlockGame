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

	engine::Program window_program;

private:
	void reload_resources();

public:
	BlockGameApplication();
	~BlockGameApplication();

	void run();

	engine::Program shader(const std::string_view& name);
	engine::Texture texture(const std::string_view& name);
};

extern BlockGameApplication* application;