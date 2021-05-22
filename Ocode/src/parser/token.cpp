#include "parser.h"

namespace ocode {
	const char* token_type_strings[] = { 
		"WORD", "INTEGER", "FLOAT", "STRING", "BOOLEAN",
		"ASSIGN", "SEPARATOR", "POINT", "COLON", "SEMICOLON", "NEWLINE",
		"COMPARE_E", "LEFT_ARROW", "RIGHT_ARROW", "COMPARE_LE", "COMPARE_GE", "COMPARE_NE", 
		"BRACKETA_OPEN", "BRACKETA_CLOSE", "BRACKETB_OPEN", "BRACKETB_CLOSE", "BRACKETC_OPEN", "BRACKETC_CLOSE"
	};

	std::string Token::to_string() {
		std::string out;
		return out + "['" + data + "', " + token_type_strings[datatype] + "]";
	}

	Tokenlist::Tokenlist() {

	}
	
	Tokenlist::~Tokenlist() {

	}

	void Tokenlist::add_token(const char* data, glm::uint8 type) {
		tokens.push_back({ data, type });
	}

	std::string Tokenlist::at(glm::uint32 pos) {
		return tokens.at(pos).data;
	}

	glm::uint32 Tokenlist::size() {
		return (glm::uint32)tokens.size();
	}

	std::string Tokenlist::to_string() {
		std::string out = "{";

		int index = 0;

		for (Token object : tokens) {
			out += object.to_string();

			if (index != tokens.size() - 1) {
				out += ", ";
			}

			index++;
		}
		return out + "}";
	}
}