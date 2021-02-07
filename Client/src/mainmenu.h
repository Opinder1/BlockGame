#pragma once

#include "game.h"

#include "cubescene.h"

class MainMenu : public Module {
private:
	engine::TextureBuffer load_texture;
	engine::Sprite title;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};