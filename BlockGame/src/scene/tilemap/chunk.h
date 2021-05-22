#pragma once

#include "ocode.h"

#include "block.h"

struct Chunk {
	Block blocks[16][16][16];

	glm::uint8 hitbox[6];
};