#include "menu_1.h"

Menu_1::Menu_1(ui::TypeStorage& types) {
	new_type(types["blockgame:background"]);
	new_type(types["blockgame:button"]);

	// TODO Currently working on this
	create<ui::Sprite>(types["blockgame:background"], glm::vec2{ 0, 0 }, 0.0f);

	create<ui::BasicButton>(types["blockgame:button"], "Singleplayer"s, glm::vec2{ 0, 150 }, 0.0f, [=] {
		singleplayer();
	});

	create<ui::BasicButton>(types["blockgame:button"], "Multiplayer"s, glm::vec2{ 0, 50 }, 0.0f, [=] {
		multiplayer();
	});

	create<ui::BasicButton>(types["blockgame:button"], "Settings"s, glm::vec2{ 0, -50 }, 0.0f, [=] {
		settings();
	});

	create<ui::BasicButton>(types["blockgame:button"], "Quit"s, glm::vec2{ 0, -150 }, 0.0f, [=] {
		quit();
	});
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