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

    class Shader {
        friend class ShaderProgram;

    private:
        uint32 shader_id;

    public:
        Shader(const Shader&) = delete;
        Shader(ShaderType type, const char* code_data, uint32 code_size);
        Shader(ShaderType type, const std::string& name);
        ~Shader();

        int compile_status() const;
        std::string get_log();
    };

    class ShaderProgram {
    private:
        uint32 program_id;

    protected:
        int link_status() const;
        std::string get_log();

        void attach(const Shader& shader);
        void link();

        void use();

    public:
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram();
        ~ShaderProgram();

        uint32 get_attribute_location(const char* name);
        uint32 get_uniform_location(const char* name);

        template<class T>
        void set(uint32 location, const T& value);

        template<class T>
        void set(int32 location, const T& value) {
            set((uint32)location, value);
        }

        template<class T>
        void set(const char* name, const T& value) {
            set(get_uniform_location(name), value);
        }
    };
}