#include "shader.h"

#include "opengl.h"

namespace engine {
    GLenum shadertype_index[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,  GL_GEOMETRY_SHADER, GL_COMPUTE_SHADER };

    Shader::Shader(ShaderType type, const char* code_data, uint32 code_size) : shader_id(glCreateShader((GLenum)type)) {
        glShaderSource(shader_id, 1, &code_data, (int32*)&code_size);

        glCompileShader(shader_id);
    }

    Shader::Shader(ShaderType type, const std::string& name) {
        shader_id = glCreateShader(shadertype_index[(uint32)type]);

        std::string file_name = "resources\\shaders\\" + name;

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
        glUseProgram(program_id);
    }

    int ShaderProgram::get_attribute(const char* name) {
        return glGetAttribLocation(program_id, name);
    }

    void ShaderProgram::set_int32(const char* name, int32 value) {
        glUniform1i(glGetUniformLocation(program_id, name), value);
    }

    void ShaderProgram::set_float(const char* name, float value) {
        glUniform1f(glGetUniformLocation(program_id, name), value);
    }

    void ShaderProgram::set_vec2(const char* name, const glm::vec2& value) {
        glUniform2f(glGetUniformLocation(program_id, name), value.x, value.y);
    }

    void ShaderProgram::set_vec3(const char* name, const glm::vec3& value) {
        glUniform3f(glGetUniformLocation(program_id, name), value.x, value.y, value.z);
    }

    void ShaderProgram::set_vec4(const char* name, const glm::vec4& value) {
        glUniform4f(glGetUniformLocation(program_id, name), value.x, value.y, value.z, value.w);
    }

    void ShaderProgram::set_mat2(const char* name, const glm::mat2& value) {
        glUniformMatrix2fv(glGetUniformLocation(program_id, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set_mat3(const char* name, const glm::mat3& value) {
        glUniformMatrix3fv(glGetUniformLocation(program_id, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set_mat4(const char* name, const glm::mat4& value) {
        glUniformMatrix4fv(glGetUniformLocation(program_id, name), 1, GL_FALSE, glm::value_ptr(value));
    }
}