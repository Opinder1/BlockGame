class Server;

#pragma once

#include "blockgame.h"

#include <unordered_map>
#include <memory>

#include "client.h"
#include "scene.h"

class Server : public ocode::WorkerThread {
private:
	NetServer server;

	std::unordered_map<uint32, ServerScene> scenes;

	std::unordered_map<ENetPeer*, std::shared_ptr<Client>> players;

public:
	ocode::LogFile log;
	ocode::Config config;

private:
	bool on_tick(const TickEvent* e);

	bool on_player_join(const PlayerJoinEvent* e);
	bool on_player_leave(const PlayerLeaveEvent* e);
	bool on_packet_recive(const PacketReciveEvent* e);

public:
	Server();
	~Server();
};

Server* server;