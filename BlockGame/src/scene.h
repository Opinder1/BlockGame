#pragma once

#include "ocode.h"

#include <thread>
#include <atomic>
#include <vector>
#include <memory>

#include "player.h"

class Scene : public ocode::WorkerThreadDelay {
private:
	ocode::Random random;

	std::vector<std::shared_ptr<Player>> clients;

public:
	Scene(const Scene&) = delete;
	Scene();
	~Scene();

	template<typename Function, typename... Args>
	void run_method(Function&& function, Args&&... args) {
		WorkerThreadDelay::post_message(function, this, args...);
	}

	void on_tick() override; 
};