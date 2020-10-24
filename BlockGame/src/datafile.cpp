#include "datafile.h"

Config::Config(std::string file_name) {
	this->file_name = file_name;

	if (!ocode::file_exists(file_name)) {
		ocode::create_file(file_name);
	}

	try {
		node = YAML::LoadFile(file_name);
	}
	catch (YAML::ParserException&) {
		return;
	}
	catch (YAML::BadFile&) {
		return;
	}
}

Config::~Config() {
	save();
}

void Config::save() {
	std::fstream file(file_name);

	file << node;
}

bool Config::initialized() {
	return !node.IsNull();
}