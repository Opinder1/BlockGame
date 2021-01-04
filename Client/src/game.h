#pragma once

#include <blockgame.h>

#include "engine/engine.h"

class Game : public engine::Layer {
private:
	NetClient client;
	Scene scene;

	engine::FPSCamera camera;

public:
	Game();
	~Game();

	void on_connect() override;
	void on_disconnect() override;

	void update() override;
};