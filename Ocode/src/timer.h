#pragma once

#include <chrono>

#include <GLM/glm.hpp>

namespace ocode {
	class Timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start;

	public:
		Timer();
		~Timer();

		glm::uint64 stop();
	};
}