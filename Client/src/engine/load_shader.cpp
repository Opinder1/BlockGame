#include "engine.h"

namespace engine {
    // TODO: Cleanup ocode file management and use code below to improve json reading. [Maybe come up with more ways of efficiently reading json]

    // Put somewhere else!
    struct json_exception {
        std::string message;
    };

    // Use this for more defined exceptions
    const std::string try_get_string(const rapidjson::Value& data, const std::string& name) {
        if (!data.HasMember(name)) throw json_exception{ std::string("Json entry '' is missing").replace(12, 0, name) };

        const rapidjson::Value& type = data[name];

        if (!type.IsString()) throw json_exception{ std::string("Json entry '' is not a string").replace(12, 0, name) };

        return type.GetString();
    }

    const rapidjson::Value::ConstArray try_get_array(const rapidjson::Value& data, const std::string& name) {
        if (!data.HasMember(name)) throw json_exception{ std::string("Json entry '' is missing").replace(12, 0, name) };

        const rapidjson::Value& type = data[name];

        if (!type.IsArray()) throw json_exception{ std::string("Json entry '' is not an array").replace(12, 0, name) };

        return type.GetArray();
    }

    ShaderType get_shader_type(const std::string& type) {
        if (type == "vertex") return ShaderType::VERTEX;
        if (type == "fragment") return ShaderType::FRAGMENT;
        if (type == "geometry") return ShaderType::GEOMETRY;
        if (type == "compute") return ShaderType::COMPUTE;

        throw shader_exception{ "Invalid shader type: " + type };
    }

    Shader Application::load_shader(const rapidjson::Value& data, const std::string& local_path) {

        Shader shader;

        ShaderType type = get_shader_type(try_get_string(data, "type"));

        std::string shader_name = local_path + "\\" + try_get_string(data, "file");

        const ocode::Resource& resource = resources.get_resource(shader_name);

        shader.new_(type, (const char*)resource.file.data, (uint32)resource.file.size);

        if (!shader.compile_status()) {
            shader.delete_();
            throw shader_exception{ "Error compiling shader '" + shader_name + "':\n" + shader.get_log() };
        }

        return shader;
    }

    Program Application::load_program(const std::string& name) {
        Program program;

        program.new_();

        try {
            const ocode::Resource& resource = resources.get_resource(name);

            rapidjson::Document data;

            data.Parse((const char*)resource.file.data, resource.file.size);

            if (data.HasParseError()) throw program_exception{ "Could not parse program json" };

            for (const auto& part : try_get_array(data, "shaders")) {
                Shader shader = load_shader(part, resource.path);
                program.attach(shader);
                shader.delete_();
            }

            program.link();

            if (!program.link_status()) throw program_exception{ "Error linking program '" + name + "':\n" + program.get_log() };

        }
        catch (json_exception& e) {
            program.delete_();
            throw program_exception{ e.message };
        }
        catch (ocode::resource_exception& e) {
            program.delete_();
            throw program_exception{ e.message + ' ' + e.resource };
        }
        catch (shader_exception& e) {
            program.delete_();
            throw program_exception{ e };
        }

        return program;
    }
}