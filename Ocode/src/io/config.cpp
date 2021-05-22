#include "config.h"

namespace ocode {
	// TOOD Not sure if this is complete
	void load_json_file(std::string file_name, json::Document& data) {
		if (!fs::exists(file_name)) throw json_exception{ "File does not exist" };

		std::ifstream file(file_name);

		if (!file) throw json_exception{ "Could not open json file" };

		json::IStreamWrapper stream(file);

		data.ParseStream(stream);

		if (data.HasParseError()) {
			throw json_exception{};
		}
	}

	// TODO Finish error handling and control flow
	void save_json_file(std::string file_name, const json::Document& data) {
		std::ofstream file(file_name);

		json::OStreamWrapper stream(file);

		json::Writer<json::OStreamWrapper> writer(stream);

		data.Accept(writer);
	}

	const std::string get_string(const json::Value& json, const std::string& name) {
		if (!json.HasMember(name)) throw json_exception{ std::string("Json entry '' is missing").replace(12, 0, name) };

		const json::Value& type = json[name];

		if (!type.IsString()) throw json_exception{ std::string("Json entry '' is not a string").replace(12, 0, name) };

		return type.GetString();
	}

	const json::Value::ConstArray get_array(const json::Value& json, const std::string& name) {
		if (!json.HasMember(name)) throw json_exception{ std::string("Json entry '' is missing").replace(12, 0, name) };

		const json::Value& type = json[name];

		if (!type.IsArray()) throw json_exception{ std::string("Json entry '' is not an array").replace(12, 0, name) };

		return type.GetArray();
	}

	Config::Config(const std::string& name) {
		file_name = name + ".yml";

		try {
			load_json_file(file_name, tree);
		}
		catch (const char*) {
			tree.SetObject();
		}
	}

	Config::~Config() {
		save();
	}

	void Config::save() {
		save_json_file(file_name, tree);
	}
}