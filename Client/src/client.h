#pragma once

#include "typedef.h"

#include "ocode.h"
#include "network.h"

class Client : private NetClient, public ocode::WorkerThread {
private:
	ocode::LogFile log;

	void on_tick() override;

	void disconnect() override;
	void packet_recive(uint8 type, PacketReader packet) override;

public:
	Client(std::string ip, uint16 port);
    ~Client();

	template<typename Function, typename... Args>
	void run_method(Function&& function, Args&&... args) {
		WorkerThread::post_message(std::bind(function, this, args...));
	}

	bool initialised();
	bool is_running();

	void connect(uint8 connect_attempts, uint16 connect_timeout);
};