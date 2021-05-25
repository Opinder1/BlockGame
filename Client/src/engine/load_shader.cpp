#include "engine.h"

namespace engine {
    ocode::File include_files(const ocode::File& file, const fs::path& path, const ResourceManager& resources, std::vector<std::string>& visited) {
        std::stringstream output;

        size_t include, first, last, begin = 0;

        while ((include = file.find("#include"s, begin)) != std::string::npos) {
            first = file.find('"', include) + 1;
            last = file.find('"', first);

            if (last == std::string::npos) continue;

            output << file.substr(begin, include - begin);

            fs::path new_path = path.parent_path() / file.substr(first, last - first);

            output << read_shader_file(new_path.lexically_normal(), resources, visited);

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

    ShaderType get_shader_type(const std::string& type) {
        if (type == "vertex"s) return ShaderType::VERTEX;
        if (type == "fragment"s) return ShaderType::FRAGMENT;
        if (type == "geometry"s) return ShaderType::GEOMETRY;
        if (type == "compute"s) return ShaderType::COMPUTE;

        throw shader_exception{ "Invalid shader type: "s + type };
    }

    Shader load_shader(const json::Value& json, const fs::path& local_path, const ResourceManager& resources) {
        ShaderType type = get_shader_type(ocode::get<std::string>(json, "type"s));

        fs::path path = local_path / ocode::get<std::string>(json, "file"s);

        std::vector<std::string> visited;

        ocode::File file = read_shader_file(path.lexically_normal(), resources, visited);

        Shader shader;

        shader._new(type, file.data(), (glm::uint32)file.size());

        if (!shader.compile_status()) {
            std::string log = shader.get_log();
            shader._delete();
            throw shader_exception{ "Error compiling shader "s + path.string() + ":\n"s + log };
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
            if (data.HasParseError()) throw program_exception{ "Could not parse program json"s };

            for (const auto& shader_json : ocode::get_array(data, "shaders"s)) {
                Shader shader = load_shader(shader_json, fs::path(name).parent_path(), resources);
                program.attach(shader);
                shader._delete();
            }

            program.link();
            if (!program.link_status()) throw program_exception{ "Error linking program "s + name + ":\n"s + program.get_log() };

        }
        catch (ocode::file_exception& e) {
            program._delete();
            throw program_exception{ e.message };
        }
        catch (shader_exception& e) {
            program._delete();
            throw program_exception{ e };
        }

        return program;
    }
}