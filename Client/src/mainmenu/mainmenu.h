#pragma once

#include "../application.h"

#include "menus/menu_1.h"
#include "menus/menu_2.h"

class MainMenu : public Module {
private:
	engine::Camera2D camera;

	std::unordered_map<std::string, engine::Program> shaders;
	std::unordered_map<std::string, engine::Font> fonts;

	std::unordered_map<std::string, std::unique_ptr<ui::Menu>> pages;
	ui::Menu* current_page;

private:
	void on_window_resize(const engine::WindowResizeEvent* e);

	void on_click(const engine::MouseClickEvent* e);

	void on_menu_event(const ui::MenuEvent* e);

public:
	MainMenu();
	~MainMenu();

	template<class Type>
	void new_page(const std::string& name) {
		static_assert(std::is_base_of<ui::Menu, Type>::value, "Should be a menu");
		pages.emplace(name, std::make_unique<Type>());
	}

	void update() override;
};