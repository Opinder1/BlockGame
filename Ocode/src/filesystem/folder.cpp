#include "filesystem.h"

namespace fs = std::filesystem;

namespace ocode {
	void create_folder_if_not_exist(const std::string& folder_name) {
		if (fs::is_directory(folder_name) && !fs::exists(folder_name)) {
			fs::create_directory(folder_name);
		}
	}

	std::string get_folder(const std::string& file_name) {
		const size_t last_slash = file_name.rfind('\\');
		if (last_slash != std::string::npos) {
			return file_name.substr(0, last_slash);
		}
		else {
			return "";
		}
	}
}