#include "../gl/shader.h"

#include "opengl.h"

namespace engine {
    template<> void Program::set(glm::uint32 location, const bool& value) {
        glProgramUniform1i(program_id, location, value);
    }


    template<> void Program::set(glm::uint32 location, const glm::int32& value) {
        glProgramUniform1i(program_id, location, value);
    }

    template<> void Program::set(glm::uint32 location, const glm::ivec2& value) {
        glProgramUniform2i(program_id, location, value.x, value.y);
    }

    template<> void Program::set(glm::uint32 location, const glm::ivec3& value) {
        glProgramUniform3i(program_id, location, value.x, value.y, value.z);
    }

    template<> void Program::set(glm::uint32 location, const glm::ivec4& value) {
        glProgramUniform4i(program_id, location, value.x, value.y, value.z, value.w);
    }


    template<> void Program::set(glm::uint32 location, const glm::uint32& value) {
        glProgramUniform1ui(program_id, location, value);
    }

    template<> void Program::set(glm::uint32 location, const glm::uvec2& value) {
        glProgramUniform2ui(program_id, location, value.x, value.y);
    }

    template<> void Program::set(glm::uint32 location, const glm::uvec3& value) {
        glProgramUniform3ui(program_id, location, value.x, value.y, value.z);
    }

    template<> void Program::set(glm::uint32 location, const glm::uvec4& value) {
        glProgramUniform4ui(program_id, location, value.x, value.y, value.z, value.w);
    }

    template<> void Program::set(glm::uint32 location, const glm::float32& value) {
        glProgramUniform1f(program_id, location, value);
    }


    template<> void Program::set(glm::uint32 location, const glm::vec2& value) {
        glProgramUniform2f(program_id, location, value.x, value.y);
    }

    template<> void Program::set(glm::uint32 location, const glm::vec3& value) {
        glProgramUniform3f(program_id, location, value.x, value.y, value.z);
    }

    template<> void Program::set(glm::uint32 location, const glm::vec4& value) {
        glProgramUniform4f(program_id, location, value.x, value.y, value.z, value.w);
    }


    template<> void Program::set(glm::uint32 location, const glm::mat2& value) {
        glProgramUniformMatrix2fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat3& value) {
        glProgramUniformMatrix3fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat4& value) {
        glProgramUniformMatrix4fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }


    template<> void Program::set(glm::uint32 location, const glm::mat2x3& value) {
        glProgramUniformMatrix2x3fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat3x2& value) {
        glProgramUniformMatrix3x2fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat2x4& value) {
        glProgramUniformMatrix2x4fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat4x2& value) {
        glProgramUniformMatrix4x2fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat3x4& value) {
        glProgramUniformMatrix3x4fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void Program::set(glm::uint32 location, const glm::mat4x3& value) {
        glProgramUniformMatrix4x3fv(program_id, location, 1, GL_FALSE, glm::value_ptr(value));
    }
}