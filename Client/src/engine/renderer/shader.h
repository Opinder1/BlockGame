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

        int get_attribute(const char* name);

        void set_int32(const char* name, int32 value);

        void set_float(const char* name, float value);

        void set_vec2(const char* name, const glm::vec2& value);
        void set_vec3(const char* name, const glm::vec3& value);
        void set_vec4(const char* name, const glm::vec4& value);

        void set_mat2(const char* name, const glm::mat2& value);
        void set_mat3(const char* name, const glm::mat3& value);
        void set_mat4(const char* name, const glm::mat4& value);
    };
}