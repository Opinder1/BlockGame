#pragma once

#include "blockgame.h"

#include "window.h"
#include "layer.h"

class Client : private ocode::EventManager {
private:
	bool running;

	ocode::LogFile log;
	Config config;

	Window window;
	LayerManager layers;

private:
	int connect();

	void tick();
	
	bool on_packet_recive(const PacketReciveEvent* e);

	bool on_window_resize(const WindowResizeEvent* e);

public:
	Client();
	~Client();
};