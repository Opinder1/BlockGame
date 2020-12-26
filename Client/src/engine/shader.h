#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include <rapidjson/document.h>

namespace engine {
    enum class ShaderType : uint32 {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        COMPUTE = GL_COMPUTE_SHADER
    };

    class Shader {
        friend class ShaderProgram;

    private:
        uint32 shader_id;

    public:
        Shader(const Shader&) = delete;
        Shader(ShaderType type, const char* code_data, int32 code_size);
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

        void use_program();

    public:
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram();
        ~ShaderProgram();

        void set_float(const char* name, float x);

        void set_vec2(const char* name, glm::vec2 value);
        void set_vec3(const char* name, glm::vec3 value);
        void set_vec4(const char* name, glm::vec4 value);

        void set_mat2(const char* name, glm::mat2& value);
        void set_mat3(const char* name, glm::mat3& value);
        void set_mat4(const char* name, glm::mat4& value);
    };
}