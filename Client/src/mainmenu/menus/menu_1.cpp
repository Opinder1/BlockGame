#include "menu_1.h"

Menu_1::Menu_1() : Menu() {
	create<ui::Background>(glm::vec2{ 0, 0 }, 0.0f);

	create<ui::BasicButton>("Singleplayer"s, glm::vec2{ 0, 150 }, 0.0f, [=] {
		singleplayer();
	});

	create<ui::BasicButton>("Multiplayer"s, glm::vec2{ 0, 50 }, 0.0f, [=] {
		multiplayer();
	});

	create<ui::BasicButton>("Settings"s, glm::vec2{ 0, -50 }, 0.0f, [=] {
		settings();
	});

	create<ui::BasicButton>("Quit"s, glm::vec2{ 0, -150 }, 0.0f, [=] {
		quit();
	});
}

void Menu_1::update() {
	update_component<ui::Background>();
	update_component<ui::BasicButton>();
}

void Menu_1::singleplayer() {
	printf("Singleplayer\n");
	application->events.event_post(ui::MenuEvent, "blockgame::menu_2"s);
}

void Menu_1::multiplayer() {
	printf("Multiplayer\n");
}

void Menu_1::settings() {
	printf("Settings\n");
}

void Menu_1::quit() {
	printf("Quit\n");
	//application->running = false;
}