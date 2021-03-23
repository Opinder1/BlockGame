#pragma once

#include <blockgame.h>

#include "../application.h"

#include "tilemap_renderer.h"

class Game : public Module {
private:
	engine::FPSCamera camera;
	engine::GlobalBuffer camera_buffer;

	engine::Surface3D surface;

	Scene scene;
	Client client;

	engine::TextureBuffer color;
	engine::TextureBuffer height;

	bool mouse_toggle = false;

public:
	Game();
	~Game();

	void controls();
	void set_camera();
	void render();
	void update() override;

	void move_camera(glm::vec3 translation);

	void on_key_action(const engine::KeyActionEvent* e);

	void on_window_resize(const engine::WindowResizeEvent* e);
};

