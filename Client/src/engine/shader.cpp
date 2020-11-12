#include "shader.h"

Shader::Shader(ShaderType type, const char* code_data, int32 code_size) {
    id = glCreateShader((uint32)type);

    glShaderSource(id, 1, &code_data, &code_size);

    glCompileShader(id);
}

Shader::Shader(ShaderType type, const std::string& file_name) {
    id = glCreateShader((uint32)type);

    if (!ocode::file_exists(file_name)) {
        printf("File %s does not exist\n", file_name.c_str());
        return;
    }

    auto f = ocode::load_file(file_name);

    const char* data = (const char*)f.get_data();
    int32 size = (int32)f.get_size();

    glShaderSource(id, 1, &data, &size);

    glCompileShader(id);

    if (compile_status() == GL_FALSE) {
        printf("(%s) ShaderError:\n%s\n", file_name.c_str(), get_log().c_str());
    }
}

Shader::~Shader() {
    glDeleteShader(id);
}

int Shader::compile_status() const {
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    return status;
}

std::string Shader::get_log() {
    int log_size;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size);

    printf("log size: %i\n", log_size);

    std::vector<char> log(log_size);
    
    glGetShaderInfoLog(id, log_size, NULL, log.data());

    return std::string(log.begin(), log.end());
}

ShaderProgram::ShaderProgram() {
    id = glCreateProgram();
}

ShaderProgram::ShaderProgram(const std::string& file_name) {
    id = glCreateProgram();

    if (!ocode::file_exists(file_name)) {
        printf("File %s does not exist\n", file_name.c_str());
        return;
    }

    rapidjson::Document data;
    ocode::load_data_file(file_name, data);

    std::string folder = ocode::get_folder(file_name) + '\\';

    printf("file: %s, folder: %s\n", file_name.c_str(), folder.c_str());

    auto& vertex_file = data["vertex"];
    auto& fragment_file = data["fragment"];
    auto& geometry_file = data["geometry"];
    auto& compute_file = data["compute"];

    if (vertex_file.IsString()) {
        printf("vertex: %s\n", (folder + vertex_file.GetString()).c_str());
        attach(Shader(ShaderType::VERTEX, folder + vertex_file.GetString()));
    }

    if (fragment_file.IsString()) {
        printf("fragment: %s\n", (folder + fragment_file.GetString()).c_str());
        attach(Shader(ShaderType::FRAGMENT, folder + fragment_file.GetString()));
    }

    if (geometry_file.IsString()) {
        printf("geometry: %s\n", (folder + geometry_file.GetString()).c_str());
        attach(Shader(ShaderType::GEOMETRY, folder + geometry_file.GetString()));
    }

    if (compute_file.IsString()) {
        attach(Shader(ShaderType::COMPUTE, folder + compute_file.GetString()));
    }

    link();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

int ShaderProgram::link_status() const {
    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    return status;
}

std::string ShaderProgram::get_log() {
    int log_size;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_size);

    std::vector<char> log(log_size);

    glGetProgramInfoLog(id, log_size, NULL, log.data());

    return std::string(log.begin(), log.end());
}

void ShaderProgram::attach(const Shader& shader) {
    if (shader.compile_status() == GL_TRUE) {
        glAttachShader(id, shader.id);
    }
}

void ShaderProgram::link() {
    glLinkProgram(id);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

void ShaderProgram::set_float(const char* name, float x) {
    glUniform1f(glGetUniformLocation(id, name), x);
}

void ShaderProgram::set_ivec2(const char* name, int x, int y) {
    glUniform2i(glGetUniformLocation(id, name), x, y);
}