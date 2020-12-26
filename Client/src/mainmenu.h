#pragma once

#include <blockgame.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "engine/engine.h"

class MainMenu : public engine::Layer {
private:
	engine::Material material;

	engine::Polygon3D poly;

public:
	MainMenu();
	~MainMenu();

	void on_connect();
	void on_disconnect();

	void update();
};