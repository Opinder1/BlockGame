#pragma once

#include "game.h"

#include "cubescene.h"

class MainMenu : public Module {
private:
	engine::TextureBuffer title;

	engine::Material material;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};