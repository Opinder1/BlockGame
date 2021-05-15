#pragma once

#include <ocode.h>

#include <rapidjson/document.h>

#include "gl.h"
#include "texture.h"

namespace engine {
    enum class ShaderType : uint32 {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        COMPUTE
    };

    struct shader_exception {
        std::string message;
    };

    struct program_exception : shader_exception {};

    class Shader {
        friend class Program;

    private:
        uint32 shader_id;

    public:
        void new_(ShaderType type, const char* code, uint32 code_size);
        void delete_();

        int compile_status();
        std::string get_log();
    };

    class Program {
    private:
        uint32 program_id;

    public:
        void new_();
        void delete_();

        void attach(const Shader& shader);
        void link();

        void use();

        int link_status();
        std::string get_log();

        uint32 get_attribute_location(const char* name);
        uint32 get_uniform_location(const char* name);

        template<class T>
        void set(uint32 location, const T& value);

        template<class T>
        void set(const char* name, const T& value) {
            set(get_uniform_location(name), value);
        }
    };
}