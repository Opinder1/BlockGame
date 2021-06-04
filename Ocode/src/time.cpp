#include "time.h"

namespace ocode {
	Timer::Timer() {
		start = chrono::high_resolution_clock::now();
	}
	
	Timer::~Timer() {

	}

	glm::uint64 Timer::stop() {
		auto end = chrono::high_resolution_clock::now();

		glm::uint64 start_count = chrono::time_point_cast<chrono::nanoseconds>(start).time_since_epoch().count();
		glm::uint64 end_count = chrono::time_point_cast<chrono::nanoseconds>(end).time_since_epoch().count();

		return end_count - start_count;
	}
}