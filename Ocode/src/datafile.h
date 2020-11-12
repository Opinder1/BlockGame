#pragma once

#include "filesystem/file.h"

#include <string>
#include <fstream>
#include <cstdio>

#include <yaml-cpp/yaml.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

namespace ocode {
	class Config {
	private:
		std::string file_name;

		YAML::Node node;

	public:
		Config(std::string file_name);
		~Config();

		void save();

		bool initialized();

		template<class Type>
		Type get_value(std::string name, Type default_value) {
			YAML::Node value = node[name];

			if (value.Type() == YAML::NodeType::Undefined) {
				node[name] = default_value;
				return default_value;
			}
			else {
				return node[name].as<Type>();
			}
		}

		template<class Type>
		void set_value(std::string name, Type&& value) {
			node[name] = value;
		}
	};

	inline void load_data_file(std::string file_name, rapidjson::Document& data) {
		if (!ocode::file_exists(file_name)) {
			ocode::create_file(file_name);
		}

		FILE* file;
		fopen_s(&file, file_name.c_str(), "rb");

		char buffer[4096];
		rapidjson::FileReadStream stream(file, buffer, sizeof(buffer));

		data.ParseStream(stream);
	}

	inline void save_data_file(std::string file_name, const rapidjson::Document& data) {
		FILE* file;
		fopen_s(&file, file_name.c_str(), "wb");

		char buffer[4096];
		rapidjson::FileWriteStream stream(file, buffer, sizeof(buffer));

		rapidjson::Writer writer(stream);
		data.Accept(writer);
	}
}