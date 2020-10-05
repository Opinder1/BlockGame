#pragma once

#include "typedef.h"

#include "uuid.h"

struct Session {
	uint64 session_id[4];

	uuid unique_id;
};