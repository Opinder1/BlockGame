#pragma once

#include "typedef.h"

namespace PacketType {
	enum types : uint8 {
		PEER_CONNECT,
		PEER_DISCONNECT,
		PLAYER_JOIN,
		PLAYER_LEAVE,
		YAML_DATA,
		JSON_DATA,

	};
}