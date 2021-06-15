#pragma once

#include "../application.h"

#include "menus/menu_1.h"
#include "menus/menu_2.h"

class MainMenu : public Module {
private:
	engine::Camera2D camera;

	std::unordered_map<std::string, engine::Program> shaders;
	std::unordered_map<std::string, engine::Font> fonts;

	ui::TypeStorage types;

	std::unordered_map<std::string, std::unique_ptr<ui::Menu>> pages;
	ui::Menu* current_page;

private:
	void on_window_resize(const engine::WindowResizeEvent* e);

	void on_click(const engine::MouseClickEvent* e);

	void on_menu_event(const ui::MenuEvent* e);

public:
	MainMenu();
	~MainMenu();

	void new_page(const std::string& name, ui::Menu* menu);

	void update() override;
};