#pragma once

#include "session.h"
#include "scene/player.h"

class Client {
private:
	Session session;

	std::wstring username;

	Player player;

public:
	Client() {};
	~Client() {};
};