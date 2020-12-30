#pragma once

#include <blockgame.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "engine/engine.h"

class Game : public engine::Layer {
private:
	NetClient client;
	Scene scene;

	engine::FPSCamera camera;

	engine::Material material;

	engine::Mesh poly;

	ocode::Random r;
	
public:
	Game();
	~Game();

	void on_connect() override;
	void on_disconnect() override;

	void update() override;

	void move_camera(glm::vec3 translation);

private:
	bool on_key_action(const engine::KeyActionEvent* e);
};