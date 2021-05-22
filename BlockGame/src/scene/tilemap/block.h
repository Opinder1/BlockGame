#pragma once

#include "ocode.h"

struct Block {
	glm::uint32 id;

	glm::uint8 get_id() const {
		return (glm::uint8&)id;
	}
};