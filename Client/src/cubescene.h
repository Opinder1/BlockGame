#pragma once

#include <blockgame.h>

#include <vector>

#include "engine/engine.h"

template<class T>
T map(T n, T a1, T b1, T a2, T b2) {
	return ((n - a1) / (b1 - a1)) * (b2 - a2) + a2;
}

class CubeScene : public engine::Layer {
private:
	engine::FPSCamera camera;

	engine::GlobalBuffer camera_buf;

	engine::Material cube_material;
	engine::Mesh cube_poly;

	ocode::Random r;

	int tick = 0;
	bool mouse_toggle = false;

	std::vector<glm::mat4> transforms;
	
public:
	CubeScene();
	~CubeScene();

	void update() override;

	void move_camera(glm::vec3 translation);

private:
	bool on_key_action(const engine::KeyActionEvent* e);
};