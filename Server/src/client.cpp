#include "client.h"

Client::Client(ocode::UUID id, std::string username, Peer connection) : id(id), username(username), connection(connection) {

}

Client::~Client() {

}

std::string Client::to_string() {
	char buffer[64];

	ENetPeer* c = (ENetPeer*)connection;

	sprintf_s(buffer, 64, "Player '%s': %u.%u.%u.%u:%u", username.c_str(), (c->address.host & 255) ^ 255, (c->address.host >> 8 & 255) ^ 255, (c->address.host >> 16 & 255) ^ 255, (c->address.host >> 24 & 255) ^ 255, c->address.port);
	
	return buffer;
}