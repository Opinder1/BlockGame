#include "parser.h"

std::unordered_map<std::string, glm::uint32> a = {
	{"include",0},
	{"define", 1},
	{"undef", 2},
	{"pragma", 3},
	{"error", 4},
	{"ifdef", 5},
	{"ifndef", 6},
	{"if", 7},
	{"endif", 8},
	{"else", 9},
	{"elif", 10}
};

int parse_directive(const char* input, std::vector<char>& buffer) {

	glm::uint32 pos = 0;

	buffer.clear();

	do {
		buffer.push_back(input[pos]);

		pos++;
	} while (input[pos] != '\n');

	return pos;
}

int parse_until_newline(const char* input) {

	glm::uint32 pos = 0;

	do {
		pos++;
	} while (input[pos] != '\n');

	return pos;
}

namespace ocode {
	int preprocess(const char* input, char* output_char) {

		glm::uint32 pos = 0;

		std::vector<char> output;

		std::vector<char> buffer;
		
		do {
			if (input[pos] == '#') {
				pos += parse_directive(input + pos, buffer);
			} else {
				pos += parse_until_newline(input + pos);
			}

		} while (input[pos] != '\0');

		// (!) data will be deleted when gone out of scope :(
		output_char = output.data();

		return -1;
	}
}
