#pragma once

#include "ocode.h"

struct Block {
	uint32 id;

	uint8 get_id() const {
		return (uint8&)id;
	}
};