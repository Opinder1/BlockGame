#pragma once

#include "../application.h"

#include "ui.h"

class MainMenu : public Module {
private:
	engine::Program material;
	engine::Texture2D texture;

	glm::uint8 state;

	engine::Scene2D scene;
	engine::Camera2D camera;

	std::vector<std::unique_ptr<ui::Element>> main_page;
	std::vector<std::unique_ptr<ui::Element>> settings;

private:
	void on_window_resize(const engine::WindowResizeEvent* e);

public:
	MainMenu();
	~MainMenu();

	void update() override;
};