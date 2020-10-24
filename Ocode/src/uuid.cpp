#include "uuid.h"

namespace ocode {
	UUID::UUID(ocode::Random& generator) : data() {
		uint64* ptr = (uint64*)&data;

		ptr[0] = generator.generate();
		ptr[1] = generator.generate();
	}

	std::string UUID::to_string() {
		char buffer[37];
		snprintf(buffer, 37, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
		return buffer;
	}
}