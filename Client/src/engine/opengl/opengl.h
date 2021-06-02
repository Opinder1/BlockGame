#pragma once

#ifdef _DEBUG
#   define GLEW_GET_FUN(x) (glLastLine(#x, __FILE__, __LINE__), x)
#endif

#include <GL/glew.h>

#include "../renderer/gl.h"

namespace engine {
    void glLastLine(const char* function, const char* file, int line);

    constexpr GLenum gl_type(Type type) {
        const GLenum gl_types[] = { GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE };
        return gl_types[(glm::uint32)type];
    }

    constexpr glm::uint32 type_size(Type type) {
        const glm::uint32 type_sizes[] = { 1, 1, 2, 2, 4, 4, 4, 8 };
        return type_sizes[(glm::uint32)type];
    }

    constexpr GLenum culling_mode(CullingMode type) {
        const GLenum culling_types[] = { GL_FALSE, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK };
        return culling_types[(glm::uint32)type];
    }

    constexpr GLenum draw_mode(DrawMode type) {
        const GLenum draw_modes[] = { GL_FILL, GL_LINE, GL_POINT };
        return draw_modes[(glm::uint32)type];
    }
}