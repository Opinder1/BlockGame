#include "opengl.h"

namespace engine {
    void _glCheckError(const char* file, int line) {
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
            printf("%s | %s (%i)", error, file, line);
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

        printf("Debug message (%i) %s", id, message);
        printf("%s\n%s\n%s\n", source_str, type_str, severity_str);
    }

    bool renderer_init() {
        if (glewInit() != GLEW_OK) {
            return false;
        }

        //glEnable(GL_DEBUG_OUTPUT);
        //glDebugMessageCallback(gl_debug_callback, 0);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        return true;
    }

    const char* get_renderer_version() {
        return (const char*)glGetString(GL_VERSION);
    }

    const char* get_adapter_vendor() {
        return (const char*)glGetString(GL_VENDOR);
    }

    const char* get_video_adapter() {
        return (const char*)glGetString(GL_RENDERER);
    }

    void set_multisample(bool enabled) {
        if (enabled) {
            glEnable(GL_MULTISAMPLE);
        }
        else {
            glDisable(GL_MULTISAMPLE);
        }
    }

    void set_depthtest(bool enabled) {
        if (enabled) {
            glEnable(GL_DEPTH_TEST);
        }
        else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void set_alphatest(bool enabled) {
        if (enabled) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else {
            glDisable(GL_BLEND);
        }
    }

    void set_culling(GLenum type) {
        if (type != 0) {
            glEnable(GL_CULL_FACE);
            glCullFace(type);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
    }

    void set_polymode(GLenum type) {
        glPolygonMode(GL_FRONT_AND_BACK, type);
    }
}