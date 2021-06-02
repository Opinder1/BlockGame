#pragma once

#include <ocode.h>

#include <rapidjson/document.h>

#include "gl.h"
#include "texture.h"

namespace engine {
    enum class ShaderType : glm::uint32 {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        COMPUTE
    };

    class Shader {
        friend class Program;

    private:
        glm::uint32 shader_id;

    public:
        void _new(ShaderType type, const char* code, glm::uint32 code_size);
        void _delete();

        int compile_status();
        std::string get_log();
    };

    class Program {
    private:
        glm::uint32 program_id;

    public:
        void _new();
        void _delete();

        void attach(const Shader& shader);
        void link();

        void use();

        int link_status();
        std::string get_log();

        glm::uint32 get_attribute_location(const char* name);
        glm::uint32 get_uniform_location(const char* name);

        template<class T>
        void set(glm::uint32 location, const T& value);

        template<class T>
        void set(const char* name, const T& value) {
            set(get_uniform_location(name), value);
        }
    };
}