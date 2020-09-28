#pragma once

#include "typedef.h"

#include <string>

namespace ocode {
	struct UUID {
		uint64 data[2];

		std::string to_string();
	};
}