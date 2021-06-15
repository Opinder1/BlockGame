 #include "mainmenu.h"

MainMenu::MainMenu() : Module(), camera(application->window, false), current_page(0) {
	application->events.event_subscribe(engine::WindowResizeEvent, on_window_resize);
	application->events.event_subscribe(engine::MouseClickEvent, on_click);
	application->events.event_subscribe(ui::MenuEvent, on_menu_event);

	shaders.emplace("blockgame:ui"s, application->shader("mainmenu\\ui.json"sv));
	shaders.emplace("blockgame:text"s, application->shader("mainmenu\\text.json"sv));

	engine::Font f = application->font("ocraext.TTF"sv); f->set_shader(shaders.at("blockgame:text"s)); fonts.emplace("blockgame:font"s, f);

	types.emplace("blockgame:background", new ui::Sprite(shaders.at("blockgame:ui"), application->texture("mainmenu\\background.png"sv)));
	types.emplace("blockgame:button", new ui::BasicButton(shaders.at("blockgame:ui"s), application->texture("mainmenu\\button.png"sv), fonts.at("blockgame:font"s)));

	new_page("blockgame::menu_1"s, new Menu_1(types));
	new_page("blockgame::menu_2"s, new Menu_2(types));

	current_page = pages.begin()->second.get();
}

MainMenu::~MainMenu() {
	for (auto& [name, shader] : shaders) {
		shader._delete();
	}

	for (auto& [name, font] : fonts) {
		delete font;
	}

	for (auto& [name, type] : types) {
		delete type;
	}
}

void MainMenu::on_window_resize(const engine::WindowResizeEvent* e) {
	camera.calc_projection();

	camera.scale = glm::vec2{ application->window.get_size().y / 600.0f };
}

void MainMenu::on_click(const engine::MouseClickEvent* e) {
	current_page->update_component<ui::ButtonComponent>(e, camera.get_transform());
}

void MainMenu::on_menu_event(const ui::MenuEvent* e) {
	printf("Setting menu to: (%s)\n", e->name.c_str());
	current_page = pages.at(e->name).get();
}

void MainMenu::new_page(const std::string& name, ui::Menu* menu) {
	pages.emplace(name, menu);
}

void MainMenu::update() {
	engine::set_multisample(false);
	engine::set_alphatest(true);
	engine::set_depthtest(false);
	engine::set_culling(engine::CullingMode::Disabled);

	camera.use();

	current_page->update();
}