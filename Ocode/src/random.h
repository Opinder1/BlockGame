#pragma once

#include "typedef.h"

#include <string>
#include <chrono>

namespace ocode {
	struct UUID {
		uint16 data[8];

		std::string to_string();
	};

	class Random {
	private:
		uint64 seed;

	public:
		Random(const Random&) = delete;
		Random();

		uint32 new_uint32();
		int32 new_int32();
		uint64 new_uint64();
		int64 new_int64();

		UUID new_uuid();
	};
}