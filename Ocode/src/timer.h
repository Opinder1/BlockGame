#pragma once

#include <chrono>

#include <string>

#include <GLM/glm.hpp>

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