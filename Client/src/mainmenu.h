#pragma once

#include <blockgame.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "engine/engine.h"

#include "cubescene.h"
#include "game.h"

class MainMenu : public engine::Layer {
private:
	engine::Material material;

	engine::Mesh poly;

public:
	MainMenu();
	~MainMenu();

	void on_connect() override;
	void on_disconnect() override;

	void update() override;
};