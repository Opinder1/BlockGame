#include "random.h"

namespace ocode {
	std::string UUID::to_string() {
		char buffer[37];
		snprintf(buffer, 37, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
		return buffer;
	}

	Random::Random() {
		seed = std::chrono::system_clock::now().time_since_epoch().count() + std::chrono::high_resolution_clock::now().time_since_epoch().count();
	}

	uint32 Random::new_uint32() {
		seed = 6364136223846793005 * seed + 1;
		return (uint32)seed;
	}

	int32 Random::new_int32() {
		seed = 6364136223846793005 * seed + 1;
		return (int32)seed;
	}

	uint64 Random::new_uint64() {
		seed = 6364136223846793005 * seed + 1;
		return (uint64)seed;
	}

	int64 Random::new_int64() {
		seed = 6364136223846793005 * seed + 1;
		return (int64)seed;
	}

	UUID Random::new_uuid() {
		uint64 uuid[2] = { new_uint64(), new_uint64() };

		return (UUID&)uuid;
	}
}