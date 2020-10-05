#define CLIENT

#include "typedef.h"

#include "blockgame.h"

Client* client;

int main() {

	ocode::Config config("client.yml");

	uint8 connect_attempts = (uint8)config.get_value<uint16>("connect_attempts", 5);
	uint16 connect_timeout = config.get_value<uint16>("connect_timeout", 2000);

	config.save();

	client = new Client("localhost", 1234);

	client->run_method(&Client::connect, connect_attempts, connect_timeout);

	while (client->is_running()) {

	}

	delete client;
}