#include "menu_2.h"

Menu_2::Menu_2(ui::TypeStorage& types) {
	create<ui::Sprite>(types["blockgame:background"], glm::vec2{ 0, 0 }, 0.0f);

	create<ui::BasicButton>(types["blockgame:button"], "Thing 1"s, glm::vec2{ 0, 150 }, 0.0f, [=] {
		new_thing(1);
	});

	create<ui::BasicButton>(types["blockgame:button"], "Thing 2"s, glm::vec2{ 0, 50 }, 0.0f, [=] {
		new_thing(2);
	});

	create<ui::BasicButton>(types["blockgame:button"], "Thing 3"s, glm::vec2{ 0, -50 }, 0.0f, [=] {
		new_thing(3);
	});

	create<ui::BasicButton>(types["blockgame:button"], "Thing 4"s, glm::vec2{ 0, -150 }, 0.0f, [=] {
		new_thing(4);
	});
}

void Menu_2::new_thing(int thing) {
	printf("New_thing %i\n", thing);
}