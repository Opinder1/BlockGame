#include "material.h"

namespace engine {
    Material::Material() : Material("default") {

    }

    Material::Material(const std::string& name) : texture(NULL) {
        std::string file_name = std::string(PROJECT_DIR) + "resources\\" + name + ".material";

        if (!ocode::file_exists(file_name)) {
            printf("File %s does not exist\n", file_name.c_str());
            return;
        }

        rapidjson::Document data;
        ocode::load_data_file(file_name, data);

        if (data.HasParseError()) {
            ocode::data_file_error(data);
            return;
        }

        const auto& vertex_file = data["vertex"];
        const auto& fragment_file = data["fragment"];
        const auto& geometry_file = data["geometry"];

        if (vertex_file.IsString()) attach(Shader(ShaderType::VERTEX, vertex_file.GetString()));
        if (fragment_file.IsString()) attach(Shader(ShaderType::FRAGMENT, fragment_file.GetString()));
        if (geometry_file.IsString()) attach(Shader(ShaderType::GEOMETRY, geometry_file.GetString()));

        link();

        if (link_status() == GL_FALSE) printf("ProgramError:\n%s\n", get_log().c_str());

        const auto& texture_file = data["texture"];

        if (texture_file.IsString()) {
            texture = new Texture(texture_file.GetString());
        }
    }

    Material::~Material() {
        if (texture != nullptr) {
            delete texture;
        }
    }

    void Material::use() {
        ShaderProgram::use();
    }
}