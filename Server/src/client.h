#pragma once

#include "ocode.h"
#include "network.h"

#include <string>

class Client {
private:
	ocode::UUID id;
	std::string username;

	Peer connection;

public:
	Client(ocode::UUID id, std::string username, Peer connection);
	~Client();

	std::string to_string();
};