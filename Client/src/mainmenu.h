#pragma once

#include <blockgame.h> 

#include "layer.h"

#include "engine/engine.h"

class MainMenu : public Layer {
private:
	Texture texture;

	engine::Polygon poly;

public:
	MainMenu();
	~MainMenu();

	void on_connect();
	void on_disconnect();

	void update();
};