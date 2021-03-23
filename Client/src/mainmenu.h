#pragma once

#include "application.h"

#include "cubescene.h"
#include "game/game.h"

#include "mainmenu/ui.h"

class MainMenu : public Module {
private:
	engine::Material material;
	engine::TextureBuffer texture;

	std::vector<std::unique_ptr<ui::Element>> boxes;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};