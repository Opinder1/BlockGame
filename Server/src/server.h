#pragma once

#include <thread>
#include <atomic>
#include <unordered_map>

#include "ocode.h"
#include "network.h"

#include "commands.h"
#include "client.h"
#include "scene.h"

#define COMMAND(name) int name(Server* server, uint8 argc, std::string* argv)

class Server : private NetServer, public ocode::WorkerThread {
private:
	std::unordered_map<uint32, std::unique_ptr<Scene>> scenes;

	std::unordered_map<Peer, std::shared_ptr<Client>> players;

	void on_tick() override;

	void connect(Peer peer) override;
	void disconnect(Peer peer) override;
	void packet_recive(Peer peer, uint8 type, PacketReader packet) override;

public: //Should be removed
	Commands<Server> commands;

	ocode::LogFile log;

public:
	Server(uint16 port, uint8 max_connections);
	~Server();

	template<typename Function, typename... Args>
	void run_method(Function&& function, Args&&... args) {
		WorkerThread::post_message(function, this, args...);
	}

	bool initialised();
	bool is_running();

	void player_join(Peer client, PacketReader& packet);
	void player_leave(Peer client, PacketReader& packet);

	void new_scene(uint32 id);
};