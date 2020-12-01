#pragma once

#include <ocode.h>

#include "layer.h"

#include "engine/engine.h"

class Client : private ocode::EventManager {
	friend void client_init();

public:
	bool running;

	ocode::LogFile log;
	ocode::Config config;

	engine::Window window;
	LayerManager layers;

private:
	Client();

	bool on_window_resize(const engine::WindowResizeEvent* e);
	bool on_window_close(const engine::WindowCloseEvent* e);

public:
	~Client();

	void run();
	void update();

	ocode::EventManager* get_manager();
};

extern Client* client;

void client_init();

void client_run(Layer* initial_layer);