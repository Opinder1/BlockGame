#pragma once

#include "../menu_components.h"

class Menu_1 : public ui::Menu {
public:
	Menu_1();

	void update() override;

	void singleplayer();

	void multiplayer();

	void settings();

	void quit();
};