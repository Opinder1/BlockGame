#pragma once

#include "ocode.h"

#include <unordered_map>
#include <vector>

#include "entity.h"

class Scene {
private:
	ocode::Random random;

	std::unordered_map<glm::uint32, std::vector<Entity*>> entities;

	ocode::EventManager& manager;

public:
	Scene(ocode::EventManager& manager) : manager(manager) {}
};