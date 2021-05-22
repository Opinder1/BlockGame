#include "../renderer/shader.h"

#include "opengl.h"

namespace engine {
    GLenum shadertype_index[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,  GL_GEOMETRY_SHADER, GL_COMPUTE_SHADER };

    glm::uint32 current_program = 0;

    void Shader::new_(ShaderType type, const char* code, glm::uint32 code_size) {
        shader_id = glCreateShader(shadertype_index[(glm::uint32)type]);

        glShaderSource(shader_id, 1, &code, (glm::int32*)&code_size);

        glCompileShader(shader_id);
    }

    void Shader::delete_() {
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

        std::vector<char> log(log_size);

        glGetShaderInfoLog(shader_id, log_size, NULL, log.data());

        return std::string(log.begin(), log.end());
    }

    void Program::new_() {
        program_id = glCreateProgram();
    }

    void Program::delete_() {
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

        std::vector<char> log(log_size);

        glGetProgramInfoLog(program_id, log_size, NULL, log.data());

        return std::string(log.begin(), log.end());
    }

    glm::uint32 Program::get_attribute_location(const char* name) {
        return glGetAttribLocation(program_id, name);
    }

    glm::uint32 Program::get_uniform_location(const char* name) {
        return glGetUniformLocation(program_id, name);
    }
}