#include "uuid.h"

std::string uuid::to_string() {
	return std::to_string(first) + " " + std::to_string(last);
}
	
uuid uuid::generate(ocode::Random& generator) {
	return { generator.generate(), generator.generate() };
}