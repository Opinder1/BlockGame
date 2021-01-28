#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace engine {
    enum class Type : uint32 {
        int8,
        uint8,
        int16,
        uint16,
        int32,
        uint32,
        float32,
        float64
    };

	GLenum gl_type(Type type);
    uint32 type_size(Type type);

    enum class BufferType : GLenum {
        Static = GL_STATIC_DRAW,
        Dynamic = GL_DYNAMIC_DRAW,
        Stream = GL_STREAM_DRAW
    };

	void glCheckError(const char* file, int line);
	#define check_error() glCheckError(__FILE__, __LINE__)

    void gl_init();
}