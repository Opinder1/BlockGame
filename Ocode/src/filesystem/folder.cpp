#include "filesystem.h"

namespace fs = std::filesystem;

namespace ocode {
	void create_folder_if_not_exist(const std::string& folder_name) {
		if (!fs::is_directory(folder_name) || !fs::exists(folder_name)) {
			fs::create_directory(folder_name);
		}
	}
}