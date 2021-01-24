#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace engine {
	// Function to convert template type into opengl type constant at compile time
	template<class T> GLenum gl_type();

    // C++ enum for opengl buffer usage types
    enum class BufferType : GLenum {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW,
        STREAM = GL_STREAM_DRAW
    };

	void glCheckError_(const char* file, int line);
	#define glCheckError() glCheckError_(__FILE__, __LINE__)

    void gl_init();
}