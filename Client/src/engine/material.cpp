#include "material.h"

namespace engine {
    Material::Material() : Material("default") {

    }

    Material::Material(const std::string& name) : texture(NULL) {
        std::string file_name = "resources\\" + name + ".material";

        if (!ocode::file_exists(file_name)) {
            printf("File %s does not exist\n", file_name.c_str());
            return;
        }

        rapidjson::Document data;
        ocode::load_data_file(file_name, data);

        auto& vertex_file = data["vertex"];
        auto& fragment_file = data["fragment"];
        auto& geometry_file = data["geometry"];

        if (vertex_file.IsString()) program.attach(Shader(ShaderType::VERTEX, vertex_file.GetString()));
        if (fragment_file.IsString()) program.attach(Shader(ShaderType::FRAGMENT, fragment_file.GetString()));
        if (geometry_file.IsString()) program.attach(Shader(ShaderType::GEOMETRY, geometry_file.GetString()));

        program.link();
         
        if (program.link_status() == GL_FALSE) printf("ProgramError:\n%s\n", program.get_log().c_str());

        auto& texture_file = data["texture"];

        if (texture_file.IsString()) {
            texture = new Texture(texture_file.GetString());
        }
    }

    Material::~Material() {
        if (texture != NULL) {
            delete texture;
        }
    }

    void Material::use() {
        program.use();
    }
}