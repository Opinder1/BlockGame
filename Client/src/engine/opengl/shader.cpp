#include "../renderer/shader.h"

#include "opengl.h"

namespace engine {
    constexpr GLenum shader_type(ShaderType type) {
        const GLenum shader_types[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, GL_COMPUTE_SHADER };
        return shader_types[(glm::uint32)type];
    }

    glm::uint32 current_program = 0;

    void Shader::_new(ShaderType type, const char* code, glm::uint32 code_size) {
        shader_id = glCreateShader(shader_type(type));

        glShaderSource(shader_id, 1, &code, (glm::int32*)&code_size);

        glCompileShader(shader_id);
    }

    void Shader::_delete() {
        glDeleteShader(shader_id);
    }

    int Shader::compile_status() {
        int status;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
        return status;
    }

    std::string Shader::get_log() {
        int log_size;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);

        std::unique_ptr<char[]> log(new char[log_size]);

        glGetShaderInfoLog(shader_id, log_size, NULL, log.get());

        return std::string(log.get(), log_size);
    }

    void Program::_new() {
        program_id = glCreateProgram();
    }

    void Program::_delete() {
        glDeleteProgram(program_id);
    }

    void Program::attach(const Shader& shader) {
        glAttachShader(program_id, shader.shader_id);
    }

    void Program::link() {
        glLinkProgram(program_id);
    }

    void Program::use() {
        if (current_program != program_id) {
            glUseProgram(program_id);
            current_program = program_id;
        }
    }

    int Program::link_status() {
        int status;
        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        return status;
    }

    std::string Program::get_log() {
        int log_size;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);

        std::unique_ptr<char[]> log(new char[log_size]);

        glGetProgramInfoLog(program_id, log_size, NULL, log.get());

        return std::string(log.get(), log_size);
    }

    glm::uint32 Program::get_attribute_location(const char* name) {
        glm::uint32 location = glGetAttribLocation(program_id, name);
        return location;
    }

    glm::uint32 Program::get_uniform_location(const char* name) {
        glm::uint32 location = glGetUniformLocation(program_id, name);
        return location;
    }
}