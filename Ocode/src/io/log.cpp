#include "log.h"

namespace ocode {
	LogFile::LogFile(const fs::path& path) : stream(path) {
		if (!stream.is_open()) {
			throw log_exception{ "Could not open log file"sv, path.u8string() };
		}
	}
}