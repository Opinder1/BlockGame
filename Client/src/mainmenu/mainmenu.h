#pragma once

#include <blockgame.h>

#include "../engine/engine.h"

#include "../cubescene.h"
#include "../game.h"

#include "ui.h"

class MainMenu : public engine::Layer {
private:
	engine::TextureBuffer texture;
	engine::Sprite title;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};