#pragma once

#include <blockgame.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "engine/engine.h"

class MainMenu : public engine::Layer {
private:
	engine::Camera camera;

	engine::Material material;

	engine::Mesh poly;

public:
	MainMenu();
	~MainMenu();

	void on_connect();
	void on_disconnect();

	void update();

	bool on_window_resize(const engine::WindowResizeEvent* e);
	bool on_key_action(const engine::KeyActionEvent* e);
};