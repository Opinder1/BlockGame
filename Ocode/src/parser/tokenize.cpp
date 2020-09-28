#include "parser.h"

#define any_number '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9'
#define any_lowercase 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z'
#define any_uppercase 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z'

bool is_number(char s) {
    return s > 47 and s < 58;
}

bool is_lowercase(char s) {
    return s > 96 and s < 123;
}

bool is_uppercase(char s) {
    return s > 64 and s < 1;
}

int get_number(const char* input, std::vector<char>& buffer, bool& isdecimal) {

    uint32 pos = 0;

    buffer.clear();

    do {
        switch (input[pos]) {
        case '.':
            if (isdecimal) {
                return -1;
            } else {
                isdecimal = true;
            }

        case '-':
        case any_number:
            buffer.push_back(input[pos]);

            pos++;

            break;

        case 'f':
            buffer.push_back('\0');
            return pos + 1;

        default:
            buffer.push_back('\0');
            return pos;
        }

    } while (input[pos] != '\0');

    buffer.push_back('\0');

    return pos;
}

int get_word(const char* input, std::vector<char>& buffer) {

    uint32 pos = 0;

    buffer.clear();

    do {
        switch (input[pos]) {
        case '_':
        case any_number:
        case any_lowercase:
        case any_uppercase:
            buffer.push_back(input[pos]);

            pos++;

            break;

        default:
            buffer.push_back('\0');

            return pos;
        }
    } while (input[pos] != '\0');

    buffer.push_back('\0');

    return pos;
}

int get_string_1(const char* input, std::vector<char>& buffer) {

    uint32 pos = 0;

    buffer.clear();

    do {
        switch (input[pos]) {
        case '"':
            buffer.push_back('\0');

            pos++;

            return pos;

        case '\\':
            if (input[pos + 1] == '"') {
                buffer.push_back('"');

                pos += 2;

                break;
            }

        default:
            buffer.push_back(input[pos]);

            pos++;
        }
    } while (input[pos] != '\0');

    return -1;
}

int get_string_2(const char* input, std::vector<char>& buffer) {

    uint32 pos = 0;

    buffer.clear();

    do {
        switch (input[pos]) {
        case '\'':
            buffer.push_back('\0');

            pos++;

            return pos;

        case '\\':
            if (input[pos + 1] == '\'') {
                buffer.push_back('\'');

                pos += 2;

                break;
            }

        default:
            buffer.push_back(input[pos]);

            pos++;
        }
    } while (input[pos] != '\0');

    return -1;
}

namespace ocode {
    int tokenize(const char* input, Tokenlist& output) {

        uint32 pos = 0;

        std::vector<char> buffer;
        
        uint32 size;

        bool isdecimal;

        do {
            switch (input[pos]) {
            case '.':
                if (!is_number(input[pos + 1])) {
                    pos += 1;

                    output.add_token(".", Token::POINT);

                    break;
                }
            case '-':
                if (!is_number(input[pos + 1]) and input[pos + 1] != '.') {
                    return pos;
                }

            case any_number:
                isdecimal = false;

                size = get_number(input + pos, buffer, isdecimal);

                if (size == -1) {
                    return pos;
                }

                pos += size;

                if (isdecimal) {
                    output.add_token(buffer.data(), Token::FLOAT);
                } else {
                    output.add_token(buffer.data(), Token::INTEGER);
                }

                break;

            case '_':
            case any_lowercase:
            case any_uppercase:
                pos += get_word(input + pos, buffer);

                output.add_token(buffer.data(), Token::WORD);

                break;

            case '"':
                pos += 1;

                size = get_string_1(input + pos, buffer);

                if (size == -1) {
                    return pos;
                }

                pos += size;

                output.add_token(buffer.data(), Token::STRING);

                break;

            case '\'':
                pos += 1;

                size = get_string_2(input + pos, buffer);

                if (size == -1) {
                    return pos;
                }

                pos += size;

                output.add_token(buffer.data(), Token::STRING);

                break;

            case '=':
                if(input[pos + 1] == '=') {
                    pos += 2;

                    output.add_token("==", Token::COMPARE_E);
                } else {
                    pos++;

                    output.add_token("=", Token::ASSIGN);
                }
                break;

            case '<':
                if (input[pos + 1] == '=') {
                    pos += 2;

                    output.add_token("<=", Token::COMPARE_LE);
                }
                else {
                    pos++;

                    output.add_token("<", Token::LEFT_ARROW);
                }
                break;

            case '>':
                if (input[pos + 1] == '=') {
                    pos += 2;

                    output.add_token(">=", Token::COMPARE_GE);
                }
                else {
                    pos++;

                    output.add_token(">", Token::RIGHT_ARROW);
                }
                break;

            case ',':
                pos++;

                output.add_token(",", Token::SEPARATOR);
                break;

            case ':':
                pos++;

                output.add_token(":", Token::COLON);
                break;

            case ';':
                pos++;

                output.add_token(";", Token::SEMICOLON);
                break;

            case '(':
                pos++;

                output.add_token("(", Token::BRACKETA_OPEN);
                break;

            case ')':
                pos++;

                output.add_token(")", Token::BRACKETA_CLOSE);
                break;

            case '[':
                pos++;

                output.add_token("[", Token::BRACKETB_OPEN);
                break;

            case ']':
                pos++;

                output.add_token("]", Token::BRACKETB_CLOSE);
                break;

            case '{':
                pos++;

                output.add_token("{", Token::BRACKETC_OPEN);
                break;

            case '}':
                pos++;

                output.add_token("}", Token::BRACKETC_CLOSE);
                break;

            case '\n':
                pos++;

                output.add_token("\n", Token::NEWLINE);
                break;

            case ' ':
                pos++;
                break;

            default:
                return pos;
            }

        } while (input[pos] != '\0');

        return -1;
    }
}