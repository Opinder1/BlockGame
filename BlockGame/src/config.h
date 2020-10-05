#pragma once

#include "typedef.h"

#include <string>
#include <fstream>

#include <yaml-cpp/yaml.h>

#include "ocode.h"

namespace ocode {
	class Config {
	private:
		std::string file_name;

		YAML::Node node;

	public:
		Config(std::string file_name);
		~Config();

		void save();

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
}