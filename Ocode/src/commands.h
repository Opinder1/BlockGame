#pragma once

#include "typedef.h"

#include <string>
#include <unordered_map>

#include "parser/parser.h"
#include "filesystem/log.h"

#define COMMAND(name) int name(uint8 argc, std::string* argv)

namespace ocode {
	class Commands {
	private:
		typedef int(*CommandType)(uint8 argc, std::string* argv);

		CommandType unknown_command;

		std::unordered_map<std::string, CommandType> commands;

	public:
		Commands(const Commands&) = delete;
		Commands() : unknown_command(NULL) {}
		~Commands() {}

		void set_default(CommandType unknown_command);

		void add_command(std::string name, CommandType function_ptr);

		void remove_command(std::string name);

		int run_command(const char* full_command);

		void print_commands();
	};
}