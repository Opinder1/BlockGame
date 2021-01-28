#include "opengl.h"

namespace engine {
    GLenum gl_types[] = { GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE };
    uint32 type_sizes[] = { 1, 1, 2, 2, 4, 4, 4, 8 };

    uint32 gl_type(Type type) {
        return gl_types[(uint32)type];
    }

    uint32 type_size(Type type) {
        return type_sizes[(uint32)type];
    }

    void glCheckError(const char* file, int line) {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR) {
            const char* error;
            switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                               error = "NONE";
            }
            ocode::println("%s | %s (%i)", error, file, line);
        }
    }

    void gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        const char* source_str, * type_str, * severity_str;

        switch (source) {
        case GL_DEBUG_SOURCE_API:             source_str = "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_str = "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_str = "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_str = "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_str = "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_str = "Source: Other"; break;
        default:                              source_str = "Source: ";
        }

        switch (type) {
        case GL_DEBUG_TYPE_ERROR:               type_str = "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_str = "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_str = "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_str = "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_str = "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_str = "Type: Other"; break;
        default:                                type_str = "Type: ";
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         severity_str = "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severity_str = "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severity_str = "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_str = "Severity: notification"; break;
        default:                             severity_str = "Severity: ";
        }

        ocode::println("Debug message (%i) %s", id, message);
        ocode::println("%s\n%s\n%s\n", source_str, type_str, severity_str);
    }

    void gl_init() {
        if (glewInit() != GLEW_OK) {
            throw "Failed to initialise glew";
        }

        glEnable(GL_DEBUG_OUTPUT);
        //glDebugMessageCallback(gl_debug_callback, 0);

        ocode::println("GL Version: %s\n", glGetString(GL_VERSION));
    }
}