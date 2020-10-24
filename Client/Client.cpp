#include "src/client.h"

Client* client;

int main() {
	client = new Client();
	
	delete client;
}