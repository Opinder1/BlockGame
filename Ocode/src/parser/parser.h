#pragma once

#include <GLM/glm.hpp>

#include <unordered_map>
#include <vector>
#include <string>

using namespace std::string_literals;

// TODO Unused

namespace ocode {
	const char* token_type_strings[];

	struct Token {
		std::string data;
		glm::uint8 datatype;

		enum TOKEN_TYPE {
			WORD, INTEGER, FLOAT, STRING, BOOLEAN,
			ASSIGN, SEPARATOR, POINT, COLON, SEMICOLON, NEWLINE,
			COMPARE_E, LEFT_ARROW, RIGHT_ARROW, COMPARE_LE, COMPARE_GE, COMPARE_NE,
			BRACKETA_OPEN, BRACKETA_CLOSE, BRACKETB_OPEN, BRACKETB_CLOSE, BRACKETC_OPEN, BRACKETC_CLOSE
		};

		std::string to_string();
	};

	struct Tokenlist {
		std::vector<Token> tokens;

		Tokenlist();

		~Tokenlist();

		void add_token(const char* data, glm::uint8 type);

		std::string at(glm::uint32 pos);

		glm::uint32 size();

		std::string to_string();
	};

	int preprocess(const char* input, char* output);

	int tokenize(const char* input, Tokenlist& output);

}