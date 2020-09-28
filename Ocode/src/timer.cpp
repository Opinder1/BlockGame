#include "timer.h"

namespace ocode {
	Timer::Timer() {
		this->start = std::chrono::high_resolution_clock::now();
	}
	
	Timer::~Timer() {

	}

	uint64 Timer::stop() {

		auto end = std::chrono::high_resolution_clock::now();

		uint64 start_milliseconds = std::chrono::time_point_cast<std::chrono::nanoseconds>(this->start).time_since_epoch().count();
		uint64 end_milliseconds = std::chrono::time_point_cast<std::chrono::nanoseconds>(end).time_since_epoch().count();

		return end_milliseconds - start_milliseconds;

	}
}