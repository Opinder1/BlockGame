#include "shader.h"

#include "opengl.h"

namespace engine {
    GLenum shadertype_index[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,  GL_GEOMETRY_SHADER, GL_COMPUTE_SHADER };

    uint32 current_program = 0;

    Shader::Shader(ShaderType type, const char* code_data, uint32 code_size) : shader_id(glCreateShader((GLenum)type)) {
        glShaderSource(shader_id, 1, &code_data, (int32*)&code_size);

        glCompileShader(shader_id);
    }

    Shader::Shader(ShaderType type, const std::string& name) {
        shader_id = glCreateShader(shadertype_index[(uint32)type]);

        std::string file_name = std::string("C:\\VisualStudio\\BlockGame\\Client\\") + "resources\\shaders\\" + name;

        if (!ocode::file_exists(file_name)) {
            printf("File %s does not exist\n", file_name.c_str());
            return;
        }

        const auto f = ocode::load_file(file_name);

        const char* data = (const char*)f.get_data();
        uint32 size = f.get_size();

        glShaderSource(shader_id, 1, &data, (int32*)&size);

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

    ShaderProgram::ShaderProgram() : program_id(glCreateProgram()) {

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
        if (current_program != program_id) {
            glUseProgram(program_id);
            current_program = program_id;
        }
    }

    uint32 ShaderProgram::get_attribute_location(const char* name) {
        return glGetAttribLocation(program_id, name);
    }

    uint32 ShaderProgram::get_uniform_location(const char* name) {
        return glGetUniformLocation(program_id, name);
    }
}