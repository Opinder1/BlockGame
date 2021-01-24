#pragma once

#include "ocode.h"

#include <unordered_map>
#include <vector>

#include "entity.h"

class Scene : ocode::EventDevice {
private:
	ocode::Random random;

	std::unordered_map<uint32, std::vector<Entity*>> entities;

public:
	Scene(ocode::EventManager* manager) : ocode::EventDevice(manager) {}
};