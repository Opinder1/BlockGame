#pragma once

#include "application.h"

class MainMenu : public engine::Layer {
private:
	engine::TextureBuffer texture;
	engine::Sprite title;

public:
	MainMenu();
	~MainMenu();

	void update() override;
};