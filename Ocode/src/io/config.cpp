#include "config.h"

namespace ocode {
	void load_json_file(const fs::path& path, json::Document& data) {
		if (!fs::exists(path)) throw json_exception{ "File does not exist" };

		std::ifstream file(path);
		if (!file) throw json_exception{ "Could not open json file" };

		json::IStreamWrapper stream(file);

		data.ParseStream(stream);
		if (data.HasParseError()) throw json_exception{ "Could not parse json file" };
	}

	void save_json_file(const fs::path& path, const json::Document& data) {
		std::ofstream file(path);
		if (!file) throw json_exception{ "Could not open json file" };

		json::OStreamWrapper stream(file);
		json::Writer<json::OStreamWrapper> writer(stream);

		if (!data.Accept(writer)) throw json_exception{ "Could not save to json file" };
	}

	const json::Value::ConstObject get(const json::Value& json, const std::string& name) {
		if (!json.HasMember(name)) throw json_exception{ std::string("Json entry '' is missing").replace(12, 0, name) };

		const json::Value& type = json[name];
		if (!type.IsObject()) throw json_exception{ std::string("Json entry '' is not a string").replace(12, 0, name) };

		return type.GetObject();
	}

	const json::Value::ConstArray get_array(const json::Value& json, const std::string& name) {
		if (!json.HasMember(name)) throw json_exception{ std::string("Json entry '' is missing").replace(12, 0, name) };

		const json::Value& type = json[name];
		if (!type.IsArray()) throw json_exception{ std::string("Json entry '' is not an array").replace(12, 0, name) };

		return type.GetArray();
	}

	Config::Config(const fs::path& path) : path(path) {
		try {
			load_json_file(path, tree);
		}
		catch (json_exception&) {
			tree.SetObject();
		}
	}

	Config::~Config() {
		save();
	}

	void Config::save() {
		save_json_file(path, tree);
	}
}