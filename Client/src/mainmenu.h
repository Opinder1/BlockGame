#pragma once

#include "application.h"

#include "cubescene.h"
#include "game/game.h"

#include "mainmenu/ui.h"

class MainMenu : public Module {
private:
	engine::Material* material;
	engine::TextureBuffer* texture;

	uint8 state;

	ui::Frame main_page;
	ui::Frame settings;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};