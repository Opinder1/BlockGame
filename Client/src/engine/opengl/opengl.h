#pragma once

#include <GL/glew.h>

#include "../renderer/gl.h"

namespace engine {
    void glCheckError(const char* file, int line);

    constexpr GLenum gl_type(Type type) {
        const GLenum gl_types[] = { GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE };
        return gl_types[(glm::uint32)type];
    }

    constexpr glm::uint32 type_size(Type type) {
        const glm::uint32 type_sizes[] = { 1, 1, 2, 2, 4, 4, 4, 8 };
        return type_sizes[(glm::uint32)type];
    }
}

#define gl_error_check() glCheckError(__FILE__, __LINE__)