#include "config.h"

namespace ocode {
	void load_json_file(const fs::path& path, json::Document& data) {
		if (!fs::exists(path)) throw file_exception{ "File does not exist"sv, path.u8string() };

		std::ifstream file(path);
		if (!file.is_open()) throw file_exception{ "Could not open json file"sv, path.u8string() };

		json::IStreamWrapper stream(file);

		data.ParseStream(stream);
		if (data.HasParseError()) throw json_exception{ "Could not parse json file"sv, path.u8string() };
	}

	void save_json_file(const fs::path& path, const json::Document& data) {
		std::ofstream file(path);
		if (!file.is_open()) throw file_exception{ "Could not open json file"sv, path.u8string() };

		json::OStreamWrapper stream(file);
		json::Writer<json::OStreamWrapper> writer(stream);

		if (!data.Accept(writer)) throw json_exception{ "Could not save to json file"sv, path.u8string() };
	}

	const json::Value::ConstObject get_object(const json::Value& json, const std::string& name) {
		if (!json.HasMember(name)) throw json_exception{ "Json entry is missing"sv, name };

		const json::Value& type = json[name];
		if (!type.IsObject()) throw json_exception{ "Json entry is not a string"sv, name };

		return type.GetObject();
	}

	const json::Value::ConstArray get_array(const json::Value& json, const std::string& name) {
		if (!json.HasMember(name)) throw json_exception{ "Json entry is missing"sv, name };

		const json::Value& type = json[name];
		if (!type.IsArray()) throw json_exception{ "Json entry is not an array"sv, name };

		return type.GetArray();
	}

	Config::Config(const fs::path& path) : path(path) {
		try {
			load_json_file(path, tree);
		}
		catch (file_exception&) {
			tree.SetObject();
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