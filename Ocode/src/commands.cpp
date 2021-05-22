#include "commands.h"

namespace ocode {
	void Commands::set_default(CommandType unknown_command) {
		this->unknown_command = unknown_command;
	}

	void Commands::add_command(std::string name, CommandType function_ptr) {
		commands.try_emplace(name, function_ptr);
	}

	void Commands::remove_command(std::string name) {
		commands.erase(name);
	}

	int Commands::run_command(const char* full_command) {
		ocode::Tokenlist parts;

		int code = ocode::tokenize(full_command, parts);

		if (code != -1) {
			return -1;
		}

		std::string command_name = parts.at(0);

		std::vector<std::string> args;

		for (glm::uint16 token = 1; token < parts.size() - 1; token++) {
			args.push_back(parts.at(token));
		}

		auto command = commands.find(command_name);

		if (command == commands.end()) {
			code = unknown_command((glm::uint8)args.size(), args.data());
		}
		else {
			code = command->second((glm::uint8)args.size(), args.data());
		}

		return code;
	}

	void Commands::print_commands() {
		std::printf("Commands:");
		for (auto& [name, command] : commands) {
			std::printf(" - %s", name.c_str());
		}
}
}