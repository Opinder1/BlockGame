#pragma once

#include <ocode.h>

#include <GL/glew.h>

enum class ShaderType : uint32 {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    COMPUTE = GL_COMPUTE_SHADER
};

class Shader {
    friend class ShaderProgram;

private:
    uint32 id;

public:
    Shader(const Shader&) = delete;
    Shader(ShaderType type, const char* code_data, int32 code_size);
    Shader(ShaderType type, const std::string& file_name);
    ~Shader();

    int compile_status() const;
    std::string get_log();
};

class ShaderProgram {
private:
    uint32 id;

public:
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram();
    ShaderProgram(const std::string& file_name);
    ~ShaderProgram();

    int link_status() const;
    std::string get_log();

    void attach(const Shader& shader);
    void link();

    void use();

    void set_float(const char* name, float x);

    void set_ivec2(const char* name, int x, int y);
};