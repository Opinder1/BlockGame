#pragma once

#include <chrono>

#include "typedef.h"

namespace ocode {
	class Timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start;

	public:
		Timer();

		~Timer();

		uint64 stop();
	};
}