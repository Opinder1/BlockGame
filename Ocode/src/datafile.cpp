#include "datafile.h"

#include <iostream>

namespace ocode {
	Config::Config(const std::string& name) {
		this->file_name = name + ".yml";

		if (!file_exists(file_name)) {
			create_file(file_name);

			node = YAML::Node();

			set_value("version", 1.0);

			save();

		} else {
			node = YAML::LoadFile(file_name);
		}
	}

	Config::~Config() {
		save();
	}

	void Config::save() {
		std::ofstream file(file_name);

		file << node;
	}

	bool Config::initialized() {
		return !node.IsNull();
	}
}