#include "engine.h"

namespace engine {
    ShaderType get_shader_type(const rapidjson::Value& type) {
        std::string string(type.GetString(), type.GetStringLength());

        if (string == "vertex") return ShaderType::VERTEX;
        if (string == "fragment") return ShaderType::FRAGMENT;
        if (string == "geometry") return ShaderType::GEOMETRY;
        if (string == "compute") return ShaderType::COMPUTE;

        throw shader_exception{ "Invalid shader type: " + string };
    }

    Shader Application::load_shader_stage(const rapidjson::Value& data, const std::string& local_path) {
        if (!data.HasMember("type")) throw shader_exception{ "Shader 'type' entry is missing" };

        if (!data.HasMember("file")) throw shader_exception{ "Shader 'file' entry is missing" };

        const auto& type = data["type"];
        const auto& file = data["file"];

        Shader shader;

        if (!type.IsString()) throw shader_exception{ "Shader 'type' entry is not a string" };

        if (!file.IsString()) throw shader_exception{ "Shader 'file' entry is not a string" };

        ShaderType shader_type = get_shader_type(type);
        std::string shader_name = local_path + "\\" + file.GetString();

        const ocode::Resource& resource = resources.get_resource(shader_name);

        shader.new_(shader_type, (const char*)resource.file.data, (uint32)resource.file.size);

        if (!shader.compile_status()) {
            shader.delete_();
            throw shader_exception{ "Error compiling shader '" + shader_name + "':\n" + shader.get_log() };
        }

        return shader;
    }

    Program Application::load_shader(const std::string& name) {
        Program program;

        program.new_();

        try {
            const ocode::Resource& resource = resources.get_resource(name);

            rapidjson::Document data;

            data.Parse((const char*)resource.file.data, resource.file.size);

            if (data.HasParseError()) throw program_exception{ "Could not parse program json" };

            if (!data.HasMember("shaders")) throw shader_exception{ "Program 'shaders' entry is missing" };

            const auto& shaders = data["shaders"];

            if (!shaders.IsArray()) throw program_exception{ "Program 'shaders' entry is not array" };

            for (const auto& part : shaders.GetArray()) {
                Shader shader = load_shader_stage(part, resource.path);
                program.attach(shader);
                //shader.delete_();
            }

            program.link();

            if (!program.link_status()) throw program_exception{ "Error linking program '" + name + "':\n" + program.get_log() };

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