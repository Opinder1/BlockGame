#pragma once

#include "typedef.h"

#include "uuid.h"

#include <chrono>

namespace ocode {
	class Random {
	private:
		uint64 seed;

	public:
		Random();

		uint64 generate();

		UUID generate_uuid();
	};
}