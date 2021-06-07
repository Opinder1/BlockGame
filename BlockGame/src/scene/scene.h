#pragma once

#include <ocode.h> 

class Scene {
private:
	ocode::Random random;

	entt::registry entities;

	ocode::EventManager& manager;

public:
	Scene(ocode::EventManager& manager) : manager(manager) {}
}; 