#define _HAS_EXCEPTIONS 0

#include "typedef.h"

#include <string>
#include <iostream>
#include <fstream>

#include "src/server.h"

COMMAND(unknown) {
	server->log.println("Unknown command. Type /help for help");
	return 0;
}

COMMAND(help) {
	//server->print_commands();
	return 0;
}

COMMAND(quit) {
	server->log.println("Stopping server...");
	server->stop_running();
	return 0;
}

COMMAND(list) {
	//server->print_players();
	return 0;
}

COMMAND(broadcast) {
	if (argc > 0) {
		std::string text = argv[0];
		server->log.println("Broadcasting: %s", text.c_str());
		//server->packet_broadcast({0, (char*)text.c_str(), text.size() });
	}
	return 0;
}

COMMAND(args_test) {
	server->log.println("Args [count = %u]:", argc);
	for (int8 arg = 0; arg < argc; arg++) {
		server->log.println("Arg %u = %s", arg, argv[arg]);
	}
	return 0;
}

COMMAND(max_threads) {
	server->log.println("Max threads: %u", std::thread::hardware_concurrency());
	return 0;
}

Server server_setup(ocode::Config config) {
	uint16 port = config.get_value<uint16>("port", 1234);
	uint8 max_connections = config.get_value<uint8>("max_connections", 32);

	return Server(port, max_connections);
}

void command_setup(Server& server) {
	server.commands.set_default(unknown);
	server.commands.add_command("help", help);
	server.commands.add_command("quit", quit);
	server.commands.add_command("list", list);
	server.commands.add_command("broadcast", broadcast);
	server.commands.add_command("args_test", args_test);
	server.commands.add_command("max_threads", max_threads);
}

void command_loop(Server& server) {
	std::string command;

	while (server.is_running()) {
		std::cin >> command;

		server.commands.run_command(command.c_str());
	}
}

int main(int argc, const char** argv) {
	SetConsoleTitle(L"Voxel Engine Server");

	ocode::println("[Voxel Engine server]\nType /help for a list of commands");

	ocode::Config config("server.yml");

	if (!ocode::file_exists("server.yml")) {
		return -1;
	}

	Server server = server_setup(config);

	command_setup(server);

	command_loop(server);
}