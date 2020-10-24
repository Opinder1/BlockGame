#pragma once

#include "typedef.h"

#include <chrono>

namespace ocode {
	class Random {
	private:
		uint64 seed;

	public:
		Random(const Random&) = delete;
		Random();

		uint64 generate();
	};
}