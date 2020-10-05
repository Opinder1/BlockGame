#pragma once

#include "typedef.h"

namespace ocode {
	class Message {
	private:
		uint8* data;
		uint32 data_size;

	public:
		Message(const Message&) = delete;
	};
}