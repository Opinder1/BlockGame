#pragma once

#include "ocode.h"

#include <thread>
#include <atomic>

#include <vector>

#include "client.h"

class Scene : public ocode::WorkerThreadDelay {
private:
	ocode::Random random;

	std::vector<Client*> clients;

public:
	Scene();
	~Scene();

	template<typename Function, typename... Args>
	void run_method(Function&& function, Args&&... args) {
		WorkerThreadDelay::post_message(std::bind(function, this, args...));
	}

	void on_tick() override; 
};