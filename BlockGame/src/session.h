#pragma once

#include <ocode.h>

struct Session {
	glm::uint64 session_id[4];

	ocode::UUID unique_id;
};