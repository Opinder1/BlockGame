#pragma once

#include <string>
#include <unordered_map>

#include "ocode.h"

template<class Parent>
class Commands {
	typedef int(*CommandType)(Parent* server, uint8 argc, std::string* argv);

private:
	Parent* ptr;

	CommandType unknown_command;

	std::unordered_map<std::string, CommandType> commands;

public:
	Commands(Parent* ptr) : ptr(ptr), unknown_command(NULL) {}

	~Commands() {}

	void set_default(CommandType unknown_command) {
		this->unknown_command = unknown_command;
	}

	void add_command(std::string name, CommandType function_ptr) {
		commands.try_emplace(name, function_ptr);
	}

	void remove_command(std::string name) {
		commands.erase(name);
	}

	int run_command(const char* full_command) {
		ocode::Tokenlist parts;

		int code = ocode::tokenize(full_command, parts);

		if (code != -1) {
			return -1;
		}

		std::string command_name = parts.at(0);

		std::vector<std::string> args;

		for (uint16 token = 1; token < parts.size() - 1; token++) {
			args.push_back(parts.at(token));
		}

		auto command = commands.find(command_name);

		if (command == commands.end()) {
			code = unknown_command(ptr, (uint8)args.size(), args.data());
		}
		else {
			code = command->second(ptr, (uint8)args.size(), args.data());
		}

		return code;
	}

	void print_commands() {
		ocode::println("Commands:");
		for (auto command : commands) {
			ocode::println(" - %s", command.first);
		}
	}
};