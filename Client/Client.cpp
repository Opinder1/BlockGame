#include "src/client.h"

int main() {
	ocode::Config config("client.yml");

	uint8 connect_attempts = config.get_value<uint8>("connect_attempts", 5);
	uint16 connect_timeout = config.get_value<uint16>("connect_timeout", 2000);

	config.save();

	Client client("localhost", 1234);

	client.run_method(&Client::connect, connect_attempts, connect_timeout);

	while (client.is_running()) {

	}
}