#pragma once

#include "typedef.h"

#include "ocode.h"
#include "network.h"

#include "packet.h"
#include "session.h"

class Client : private network::Client, public ocode::WorkerThread {
private:
	ocode::LogFile log;

	bool initialised();
	 
	void on_tick() override;

	void packet_recive(network::Peer peer, uint8 type, network::PacketReader& packet) override;

public:
	Client(const Client&) = delete;
	Client(std::string ip, uint16 port);
    ~Client();

	template<typename Function, typename... Args>
	void run_method(Function&& function, Args&&... args) {
		WorkerThread::post_message(function, this, args...);
	}

	bool is_running();

	void connect(uint8 connect_attempts, uint16 connect_timeout); 
}; 