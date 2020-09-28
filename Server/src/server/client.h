#pragma once

#include "engine.h"

#include <string>

class Client {
private:
	ocode::UUID id;
	std::string username;

	Peer connection;

	inline static ocode::Random random;

public:
	Client(std::string username, Peer connection);
	~Client();

	std::string to_string();
};