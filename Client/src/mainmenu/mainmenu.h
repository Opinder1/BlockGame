#pragma once

#include <blockgame.h>

#include "../engine/engine.h"

#include "../cubescene.h"
#include "../game.h"

#include "ui.h"

class MainMenu : public engine::Layer {
private:
	engine::Sprite title;

public:
	MainMenu();
	~MainMenu();

	void on_connect() override;
	void on_disconnect() override;

	void update() override;
};