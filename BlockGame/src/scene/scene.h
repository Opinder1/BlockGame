#pragma once

#include "ocode.h"

#include <vector>

#include "entity.h"

class Scene : ocode::EventDevice {
private:
	ocode::Random random;

	std::vector<Entity*> entities;

public:
	Scene(ocode::EventManager* manager) : ocode::EventDevice(manager) {}
};