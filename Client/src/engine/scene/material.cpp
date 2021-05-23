#include "material.h"

namespace engine {
    Material::Material() : Material("default"s) {

    }

    Material::Material(const std::string& name) : texture(NULL) {

    }

    Material::~Material() {
        if (texture != nullptr) {
            delete texture;
        }
    }

    void Material::use() {
        Program::use();
    }
}