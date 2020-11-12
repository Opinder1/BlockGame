#pragma once

#include "blockgame.h"

#include "layer.h"

class Game : public Layer {
private:
	NetClient client;
	Scene& scene;

public:
	Game(ocode::EventManager* m, Scene& scene);
	~Game() override;

	void on_connect() override;
	void on_disconnect() override;

	void update() override;
};