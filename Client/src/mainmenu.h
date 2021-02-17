#pragma once

#include "application.h"

#include "cubescene.h"
#include "game/game.h"

class MainMenu : public Module {
private:
	engine::TextureBuffer title;

	engine::Material material;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};