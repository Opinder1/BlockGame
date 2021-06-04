#pragma once

#include <string>
#include <chrono>

#include "math.h"

namespace chrono = std::chrono;

using namespace std::chrono_literals;

namespace ocode {
	class Timer {
	private:
		chrono::time_point<chrono::high_resolution_clock> start;

	public:
		Timer();
		~Timer();

		glm::uint64 stop();
	};
}