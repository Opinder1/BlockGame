#pragma once

#include "typedef.h"

#include <string>

#include "ocode.h"

struct uuid {
	uint64 first;
	uint64 last;

	std::string to_string();

	static uuid generate(ocode::Random& generator);
};