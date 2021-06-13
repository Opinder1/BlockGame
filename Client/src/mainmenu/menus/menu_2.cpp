#include "menu_2.h"

Menu_2::Menu_2() : Menu() {
	create<ui::Background>(glm::vec2{ 0, 0 }, 0.0f);

	create<ui::BasicButton>("Thing 1"s, glm::vec2{ 0, 150 }, 0.0f, [=] {
		new_thing(1);
	});

	create<ui::BasicButton>("Thing 2"s, glm::vec2{ 0, 50 }, 0.0f, [=] {
		new_thing(2);
	});

	create<ui::BasicButton>("Thing 3"s, glm::vec2{ 0, -50 }, 0.0f, [=] {
		new_thing(3);
	});

	create<ui::BasicButton>("Thing 4"s, glm::vec2{ 0, -150 }, 0.0f, [=] {
		new_thing(4);
	});
}

void Menu_2::update() {
	update_component<ui::Background>();
	update_component<ui::BasicButton>();
}

void Menu_2::new_thing(int thing) {
	printf("New_thing %i\n", thing);
}