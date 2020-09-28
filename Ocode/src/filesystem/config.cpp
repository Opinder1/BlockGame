#include "config.h"

namespace ocode {
	Config::Config(std::string file_name) {
		this->file_name = file_name;

		if (!file_exists(file_name)) {
			create_file(file_name);
		}

		node = YAML::LoadFile(file_name);
	}

	Config::~Config() {
		save();
	}

	void Config::save() {
		std::fstream file(file_name);

		file << node;
	}
}