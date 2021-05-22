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
    struct json_exception : file_exception {}; 
    
    // TODO Switch std::string to fs::directory_entry
    void load_json_file(std::string file_name, json::Document& data);

    void save_json_file(std::string file_name, const json::Document& data); 
    
    // TODO Add function for all types or use template
    const std::string get_string(const json::Value& json, const std::string& name);

    const json::Value::ConstArray get_array(const json::Value& json, const std::string& name);

    class Config {
    private:
        std::string file_name;

        json::Document tree;

    public:
        // TODO Switch std::string to fs::directory_entry
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
}