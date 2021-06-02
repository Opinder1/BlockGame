#pragma once

#include "application.h"

#include "cubescene.h"
#include "game/game.h"

#include "mainmenu/ui.h"

class MainMenu : public Module {
private:
	engine::Program material;
	engine::Texture2D texture;

	glm::uint8 state;

	engine::Scene2D scene;
	engine::Camera2D camera;

	ui::Frame main_page;
	ui::Frame settings;

private:
	void on_window_resize(const engine::WindowResizeEvent* e);

public:
	MainMenu();
	~MainMenu();

	void update() override;
};