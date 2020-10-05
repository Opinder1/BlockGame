#include "random.h"

namespace ocode {
	Random::Random() {
		seed = std::chrono::system_clock::now().time_since_epoch().count() + std::chrono::high_resolution_clock::now().time_since_epoch().count();
	}

	uint64 Random::generate() {
		seed = 6364136223846793005 * seed + 1;
		return seed;
	}
}