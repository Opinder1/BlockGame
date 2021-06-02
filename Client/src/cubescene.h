#pragma once
/*
#include <vector>

#include "application.h"

template<class T>
T map(T n, T a1, T b1, T a2, T b2) {
	return ((n - a1) / (b1 - a1)) * (b2 - a2) + a2;
}

class CubeScene : public Module {
private:
	engine::FPSCamera camera;
	engine::UniformBuffer camera_buffer;

	engine::SurfaceMS surface;

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
	void on_key_action(const engine::KeyActionEvent* e);

	void on_window_resize(const engine::WindowResizeEvent* e);
};
*/