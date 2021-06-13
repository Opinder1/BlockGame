#pragma once

#include "../menu_components.h"

class Menu_2 : public ui::Menu {
public:
	Menu_2();

	void update() override;

	void new_thing(int thing);
};