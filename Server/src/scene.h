class ServerScene;

#pragma once

#include "blockgame.h"

#include <vector>
#include <memory>

#include "client.h"

class ServerScene : private ocode::WorkerThread {
private:
	Server* server;

	std::vector<std::shared_ptr<Client>> players;

	Scene scene;

public:
	ServerScene(Server* server);

	~ServerScene();

	void on_tick();

	bool on_packet_send(const PacketSendEvent* e);
};