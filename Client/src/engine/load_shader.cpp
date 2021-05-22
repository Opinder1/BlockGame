#include "engine.h"

namespace engine {

    ShaderType get_shader_type(const std::string& type) {
        if (type == "vertex") return ShaderType::VERTEX;
        if (type == "fragment") return ShaderType::FRAGMENT;
        if (type == "geometry") return ShaderType::GEOMETRY;
        if (type == "compute") return ShaderType::COMPUTE;

        throw shader_exception{ "Invalid shader type: " + type };
    }

    Shader Application::load_shader(const json::Value& json, const std::string& local_path) {

        Shader shader;

        ShaderType type = get_shader_type(ocode::get<std::string>(json, "type"));

        std::string shader_name = local_path + "\\" + ocode::get<std::string>(json, "file");

        // TODO Implement advanced shader loading with includes and stuff
        const ocode::Resource& resource = resources[shader_name];

        shader.new_(type, (const char*)resource.file.data(), (glm::uint32)resource.file.size());

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
            const ocode::Resource& resource = resources[name];

            json::Document data;

            data.Parse((const char*)resource.file.data(), resource.file.size());

            if (data.HasParseError()) throw program_exception{ "Could not parse program json" };

            for (const auto& shader_json : ocode::get_array(data, "shaders")) {
                Shader shader = load_shader(shader_json, resource.path);
                program.attach(shader);
                shader.delete_();
            }

            program.link();

            if (!program.link_status()) throw program_exception{ "Error linking program '" + name + "':\n" + program.get_log() };

        }
        catch (ocode::file_exception& e) {
            program.delete_();
            throw program_exception{ e.message };
        }
        catch (shader_exception& e) {
            program.delete_();
            throw program_exception{ e };
        }

        return program;
    }
}