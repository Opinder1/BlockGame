#include "opengl.h"

namespace engine {
    struct {
        const char* function;
        const char* file;
        int line;
    } last_line;

    void glLastLine(const char* function, const char* file, int line) {
        last_line = { function, file, line };
        printf("(%s) %s:%i\n", function, file, line);
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

        printf("%s | %s | %s\n", source_str, type_str, severity_str);
        printf("Debug message (%i) %s\n", id, message);

        if (severity == GL_DEBUG_SEVERITY_LOW || severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_HIGH) {
            throw std::exception();
        }
    }

    bool renderer_init() {
        if (glewInit() != GLEW_OK) {
            // TODO use throw instead
            return false;
        }

        GLEW_GET_FUN(glEnable)(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(gl_debug_callback, 0);

        GLEW_GET_FUN(glClearColor)(0.0f, 0.0f, 0.0f, 0.0f);

        set_multisample(false);
        set_depthtest(false);
        set_alphatest(false);
        set_culling(CullingMode::Disabled);
        set_drawmode(DrawMode::Fill);

        glm::uint32 uniformbuffer_max_size = 0;
        glm::uint32 uniformbuffer_max_bindings = 0;
        glm::uint32 globalbuffer_max_size = 0;
        glm::uint32 globalbuffer_max_bindings = 0;

        glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, (GLint*)&uniformbuffer_max_size);
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, (GLint*)&uniformbuffer_max_bindings);
        glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, (GLint*)&globalbuffer_max_size);
        glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, (GLint*)&globalbuffer_max_bindings);

        // TODO Maybe implement glEnable(GL_PROGRAM_POINT_SIZE) although it just makes squares but that could be useful for sprites;

        std::cout << uniformbuffer_max_size << " " << uniformbuffer_max_bindings << " " << globalbuffer_max_size << " " << globalbuffer_max_bindings << std::endl;

        return true;
    }

    const std::string_view get_renderer_version() {
        return (const char*)GLEW_GET_FUN(glGetString)(GL_VERSION);
    }

    const std::string_view get_adapter_vendor() {
        return (const char*)GLEW_GET_FUN(glGetString)(GL_VENDOR);
    }

    const std::string_view get_video_adapter() {
        return (const char*)GLEW_GET_FUN(glGetString)(GL_RENDERER);
    }

    void set_multisample(bool enabled) {
        if (enabled) {
            GLEW_GET_FUN(glEnable)(GL_MULTISAMPLE);
        }
        else {
            GLEW_GET_FUN(glDisable)(GL_MULTISAMPLE);
        }
    }

    void set_depthtest(bool enabled) {
        if (enabled) {
            GLEW_GET_FUN(glEnable)(GL_DEPTH_TEST);
        }
        else {
            GLEW_GET_FUN(glDisable)(GL_DEPTH_TEST);
        }
    }

    void set_alphatest(bool enabled) {
        if (enabled) {
            GLEW_GET_FUN(glEnable)(GL_BLEND);
            GLEW_GET_FUN(glBlendFunc)(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else {
            GLEW_GET_FUN(glDisable)(GL_BLEND);
        }
    }

    void set_culling(CullingMode mode) {
        GLenum type = culling_mode(mode);

        if (type != 0) {
            GLEW_GET_FUN(glEnable)(GL_CULL_FACE);
            GLEW_GET_FUN(glCullFace)(type);
        }
        else {
            GLEW_GET_FUN(glDisable)(GL_CULL_FACE);
        }
    }

    void set_drawmode(DrawMode mode) {
        GLenum type = draw_mode(mode);

        GLEW_GET_FUN(glPolygonMode)(GL_FRONT_AND_BACK, type);
    }

    void set_viewport(glm::ivec2 pos, glm::uvec2 size) {
        GLEW_GET_FUN(glViewport)(pos.x, pos.y, size.x, size.y);
    }
}