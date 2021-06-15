#pragma once

#include "../menu_components.h"

class Menu_2 : public ui::Menu {
public:
	Menu_2(ui::TypeStorage& types);

	void new_thing(int thing);
};