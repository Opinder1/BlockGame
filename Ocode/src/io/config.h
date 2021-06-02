#pragma once

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/error/en.h>

#include "file.h"

namespace json = rapidjson;

namespace ocode {
    struct json_exception {
        std::string_view message;
        std::string name;
    };
    
    void load_json_file(const fs::path& path, json::Document& data);

    void save_json_file(const fs::path& path, const json::Document& data);
    
    template<class Type>
    const Type get(const json::Value& json, const std::string& name) {
        if (!json.HasMember(name)) throw json_exception{ "Json entry is missing"sv, name };

        const json::Value& type = json[name];

        if (!type.Is<Type>()) throw json_exception{ "Json entry is not an array"sv, name };

        return type.Get<Type>();
    }

    const json::Value::ConstObject get_object(const json::Value& json, const std::string& name);
    const json::Value::ConstArray get_array(const json::Value& json, const std::string& name);

    class Config {
    private:
        fs::path path;

        json::Document tree;

    public:
        Config(const fs::path& path);
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
}