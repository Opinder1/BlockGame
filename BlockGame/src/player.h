#pragma once

#include <string>
#include <sstream>

#include <rapidjson/document.h>

#include "ocode.h"
#include "network.h"

#include "session.h"
#include "datafile.h"

class Player {
private:
	network::Server* host;
	network::Peer peer;

	Session session;
	std::string username;

	std::string data_file_name;
	rapidjson::Document data;

public:
	Player(const Player&) = delete;
	Player(network::Server* host, network::Peer peer, Session session, std::string username);
	~Player();

	const Session& get_session();
	const std::string& get_username();

	void send_packet(network::PacketWriter& packet);
};