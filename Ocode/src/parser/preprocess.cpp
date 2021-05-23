#include "parser.h"

std::unordered_map<std::string, glm::uint32> a = {
	{"include"s,0},
	{"define"s, 1},
	{"undef"s, 2},
	{"pragma"s, 3},
	{"error"s, 4},
	{"ifdef"s, 5},
	{"ifndef"s, 6},
	{"if"s, 7},
	{"endif"s, 8},
	{"else"s, 9},
	{"elif"s, 10}
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
