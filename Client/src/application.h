#pragma once

#include <blockgame.h>

#include "engine/engine.h"

class Module {
public:
	virtual ~Module() {}

	virtual void update() = 0;
};

class BlockGameApplication : public engine::Application {
public:
	ocode::LogFile log;
	ocode::Config config;

	std::vector<std::unique_ptr<Module>> modules;

private:
	void reload_resources();

public:
	BlockGameApplication();
	~BlockGameApplication();

	template<class Type>
	void new_module() {
		static_assert(std::is_base_of<Module, Type>::value, "Should be a module");
		modules.push_back(std::make_unique<Type>());
	}

	void run();

	engine::Program shader(const std::string_view& name);
	engine::Texture texture(const std::string_view& name);
	engine::Font font(const std::string_view& name);
};

extern BlockGameApplication* application;