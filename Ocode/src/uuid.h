#pragma once

#include "typedef.h"

#include <string>

#include "random.h"

namespace ocode {
	struct UUID {
		uint16 data[8];

		UUID(ocode::Random& generator);

		std::string to_string();
	};
}