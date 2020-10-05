#pragma once

#include "typedef.h"

#include <thread>
#include <atomic>
#include <unordered_map>

#include "ocode.h"
#include "network.h"

#include "packet.h"
#include "player.h"
#include "scene.h"

class Server : private network::Server, public ocode::WorkerThread {
private:
	std::unordered_map<uint32, std::unique_ptr<Scene>> scenes;

	std::unordered_map<network::Peer, std::shared_ptr<Player>> players;

	bool initialised();

	void on_tick() override;

	void packet_recive(network::Peer peer, uint8 type, network::PacketReader& packet) override;

	void player_join(network::Peer client, network::PacketReader& packet);
	void player_leave(network::Peer client, network::PacketReader& packet);

public: //Should be removed
	ocode::LogFile log;

public:
	Server(const Server&) = delete;
	Server(uint16 port, uint8 max_connections);
	~Server();

	template<typename Function, typename... Args>
	void run_method(Function&& function, Args&&... args) {
		WorkerThread::post_message(function, this, args...);
	}

	bool is_running();
};