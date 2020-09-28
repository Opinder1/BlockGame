#include "uuid.h"

namespace ocode {
	std::string UUID::to_string() {
		return std::to_string(data[0]) + " " + std::to_string(data[1]);
	}
}