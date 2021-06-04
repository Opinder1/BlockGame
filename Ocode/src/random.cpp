#include "random.h"

namespace ocode {
	std::string UUID::to_string() {
		char buffer[37];
		snprintf(buffer, 37, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
		return buffer;
	}

	Random::Random() : seed(chrono::system_clock::now().time_since_epoch().count() + chrono::high_resolution_clock::now().time_since_epoch().count()) {

	}

	Random::Random(glm::uint64 seed) : seed(seed) {

	}

	UUID Random::new_uuid() {
		glm::uint64 uuid[2] = { get<glm::uint64>(), get<glm::uint64>() };

		return (UUID&)uuid;
	}
}