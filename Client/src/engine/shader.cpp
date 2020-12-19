#include "shader.h"

namespace engine {
    Shader::Shader(ShaderType type, const char* code_data, int32 code_size) {
        shader_id = glCreateShader((uint32)type);

        glShaderSource(shader_id, 1, &code_data, &code_size);

        glCompileShader(shader_id);
    }

    Shader::Shader(ShaderType type, const std::string& name) {
        shader_id = glCreateShader((uint32)type);

        std::string file_name = "resources\\" + name;

        if (!ocode::file_exists(file_name)) {
            printf("File %s does not exist\n", file_name.c_str());
            return;
        }

        auto f = ocode::load_file(file_name);

        const char* data = (const char*)f.get_data();
        int32 size = (int32)f.get_size();

        glShaderSource(shader_id, 1, &data, &size);

        glCompileShader(shader_id);

        if (compile_status() == GL_FALSE) {
            printf("(%s) ShaderError:\n%s\n", file_name.c_str(), get_log().c_str());
        }
    }

    Shader::~Shader() {
        glDeleteShader(shader_id);
    }

    int Shader::compile_status() const {
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

    ShaderProgram::ShaderProgram() {
        program_id = glCreateProgram();
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(program_id);
    }

    int ShaderProgram::link_status() const {
        int status;
        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        return status;
    }

    std::string ShaderProgram::get_log() {
        int log_size;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);

        std::vector<char> log(log_size);

        glGetProgramInfoLog(program_id, log_size, NULL, log.data());

        return std::string(log.begin(), log.end());
    }

    void ShaderProgram::attach(const Shader& shader) {
        glAttachShader(program_id, shader.shader_id);
    }

    void ShaderProgram::link() {
        glLinkProgram(program_id);
    }

    void ShaderProgram::use() {
        glUseProgram(program_id);
    }

    void ShaderProgram::set_float(const char* name, float x) {
        glUniform1f(glGetUniformLocation(program_id, name), x);
    }

    void ShaderProgram::set_ivec2(const char* name, int x, int y) {
        glUniform2i(glGetUniformLocation(program_id, name), x, y);
    }
}