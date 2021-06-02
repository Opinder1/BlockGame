#include "resources.h"

namespace engine {
    ocode::File include_files(const ocode::File& file, const fs::path& path, const ResourceManager& resources, std::vector<std::string>& visited) {
        std::stringstream output;

        size_t include, first, last, begin = 0;

        while ((include = file.find("#include", begin)) != std::string::npos) {
            first = file.find('"', include) + 1;
            last = file.find('"', first);

            if (last == std::string::npos) continue;

            output << file.substr(begin, include - begin);

            fs::path new_path = (path.parent_path() / file.substr(first, last - first)).lexically_normal();

            output << read_shader_file(new_path, resources, visited);

            begin = file.find('\n', include);
        }

        if (begin != std::string::npos) output << file.substr(begin);

        return output.str();
    }

    ocode::File read_shader_file(const fs::path& path, const ResourceManager& resources, std::vector<std::string>& visited) {
        const std::string& name = path.string();

        for (auto& item : visited) {
            if (item == name) return ""s;
        }

        const ocode::File& file = resources[name];

        visited.push_back(name);

        return include_files(file, path, resources, visited);
    }

    ShaderType get_shader_type(const fs::path& path, const std::string& type) {
        if (type == "vertex"sv) return ShaderType::VERTEX;
        if (type == "fragment"sv) return ShaderType::FRAGMENT;
        if (type == "geometry"sv) return ShaderType::GEOMETRY;
        if (type == "compute"sv) return ShaderType::COMPUTE;

        throw program_exception{ "Invalid shader type"sv, path.string(), type + " is not a shader type" };
    }

    Shader load_shader(const json::Value& json, const fs::path& local_path, const ResourceManager& resources) {
        fs::path path = (local_path / ocode::get<std::string>(json, "file"s)).lexically_normal();

        ShaderType type = get_shader_type(path, ocode::get<std::string>(json, "type"s));

        std::vector<std::string> visited;

        ocode::File file = read_shader_file(path, resources, visited);

        Shader shader;

        shader._new(type, file.data(), (glm::uint32)file.size());

        if (!shader.compile_status()) {
            std::string log = shader.get_log();
            shader._delete();
            throw program_exception{ "Error compiling shader "sv, path.string(), log };
        }

        return shader;
    }

    Program load_program(const std::string& name, const ResourceManager& resources) {
        Program program;

        program._new();

        try {
            const ocode::File& resource = resources[name];

            json::Document data;

            data.Parse((const char*)resource.data(), resource.size());
            if (data.HasParseError()) throw ocode::json_exception{ "Could not parse program json"sv, name };

            for (const auto& shader_json : ocode::get_array(data, "shaders"s)) {
                Shader shader = load_shader(shader_json, fs::path(name).parent_path(), resources);
                program.attach(shader);
                shader._delete();
            }

            program.link();
            if (!program.link_status()) throw program_exception{ "Error linking program "sv, name,  program.get_log() };
        }
        catch (ocode::file_exception& e) {
            program._delete();
            throw program_exception{ "Error preprocessing shader"sv, e.name, std::string{e.message} };
        }
        catch (ocode::json_exception& e) {
            program._delete();
            throw program_exception{ "Error reading program config"sv, e.name, std::string{e.message} };
        }
        catch (program_exception& e) {
            program._delete();
            throw e;
        }

        return program;
    }
}