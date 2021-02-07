#pragma once

#include <GL/glew.h>

#include "gl.h"

namespace engine {
    void _glCheckError(const char* file, int line);

    constexpr GLenum gl_types[] = { GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE };
    constexpr uint32 type_sizes[] = { 1, 1, 2, 2, 4, 4, 4, 8 };

    constexpr GLenum gl_type(Type type) {
        return gl_types[(uint32)type];
    }

    constexpr uint32 type_size(Type type) {
        return type_sizes[(uint32)type];
    }
    
    void set_multisample(bool enabled);

    void set_depthtest(bool enabled);

    void set_alphatest(bool enabled);

    void set_culling(GLenum type);

    void set_polymode(GLenum type);
}

#define glCheckError() _glCheckError(__FILE__, __LINE__)