class Client;

#pragma once

#include "blockgame.h"

#include <rapidjson/document.h>

#include <string>

#include "server.h"

class Client {
private:
	Server* server;

	ENetPeer* peer;

	Session session;
	std::wstring username;

	std::string data_file_name;
	rapidjson::Document data;

public:
	Client(const Client&) = delete;
	Client(Server* server, ENetPeer* peer, Session session, const std::wstring& username);
	~Client();

	const Session& get_session();
	const std::wstring& get_username();
	
	void send_packet(Packet* packet);
};

class PlayerJoinEvent {
private:
	ENetPeer* peer;
};

class PlayerLeaveEvent {
private:
	ENetPeer* peer;
};