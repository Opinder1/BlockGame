#include "src/server.h"

#include <string>
#include <iostream>

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
	return -1;
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

void command_setup(ocode::Commands& commands) {
	commands.set_default(unknown);
	commands.add_command("help", help);
	commands.add_command("quit", quit);
	commands.add_command("list", list);
	commands.add_command("broadcast", broadcast);
	commands.add_command("args_test", args_test);
	commands.add_command("max_threads", max_threads);
}

void command_loop() {
	ocode::Commands commands;
	std::string command;

	command_setup(commands);

	while (server->is_running()) {
		std::cin >> command;

		if (commands.run_command(command.c_str()) != 0) {
			server->stop_running();
		}
	}
}

int main(int argc, const char** argv) {
	SetConsoleTitle(L"Voxel Engine Server");

	ocode::println("[Voxel Engine server]\nType /help for a list of commands");

	Config config("server.yml");

	server = new Server();

	command_loop();

	delete server;
}