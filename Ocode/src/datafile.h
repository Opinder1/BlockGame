#pragma once

#include <string>
#include <fstream>

#include "filesystem/file.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/error/en.h>

namespace json = rapidjson;

namespace ocode {
	class Config {
	private:
		std::string file_name;

		json::Document tree;

	public:
		Config(const std::string& name);
		~Config();

		void save();

		template<class Type>
		Type get_value(const std::string& name, Type default_value) {
			json::Value key(name.c_str(), tree.GetAllocator());

			if (!tree.HasMember(key)) {
				tree.AddMember(key, default_value, tree.GetAllocator());
			}

			return tree[name].Get<Type>();
		}

		template<class Type>
		void set_value(const std::string& name, Type&& value) {
			json::Value key(name.c_str(), tree.GetAllocator());
			tree.AddMember(key, value, tree.GetAllocator());
		}
	};

	class JSON {

	};

	void load_data_file(std::string file_name, json::Document& data);

	void save_data_file(std::string file_name, const json::Document& data);

	void data_file_error(const json::Document& data);
}