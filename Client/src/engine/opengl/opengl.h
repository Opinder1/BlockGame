#pragma once

#ifdef _DEBUG
#   define GLEW_GET_FUN(x) (glLastLine(#x, __FILE__, __LINE__), x)
#endif

#include <GL/glew.h>

#include "../gl/gl.h"

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

    constexpr GLenum buffer_type(BufferType type) {
        const GLenum buffer_types[] = { GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW };
        return buffer_types[(glm::uint32)type];
    }

    constexpr GLenum draw_type(DrawType type) {
        const GLenum draw_types[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_PATCHES, GL_POINTS };
        return draw_types[(glm::uint32)type];
    }

    constexpr GLenum draw_mode(DrawMode type) {
        const GLenum draw_modes[] = { GL_FILL, GL_LINE, GL_POINT };
        return draw_modes[(glm::uint32)type];
    }

    constexpr GLenum culling_mode(CullingMode type) {
        const GLenum culling_types[] = { GL_FALSE, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK };
        return culling_types[(glm::uint32)type];
    }

	constexpr GLenum shader_type(ShaderType type) {
		const GLenum shader_types[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, GL_COMPUTE_SHADER };
		return shader_types[(glm::uint32)type];
	}

	constexpr GLenum storage_format(TextureFormat format) {
		switch (format) {
		case TextureFormat::R: return GL_RED;
		case TextureFormat::RG: return GL_RG;
		case TextureFormat::RGB: return GL_RGB;
		case TextureFormat::RGBA: return GL_RGBA;
		case TextureFormat::DEPTH_AND_STENCIL: return GL_DEPTH24_STENCIL8;
		}
		return GL_FALSE;
	}

	constexpr GLenum storage_type(TextureFormat format, Type type = Type::float64) {
		switch (format) {
		case TextureFormat::R:
			switch (type) {
			case Type::uint8: return GL_R8UI;
			case Type::uint16: return GL_R16UI;
			case Type::uint32: return GL_R32UI;
			case Type::float32: return GL_R32F;
			default: return GL_RED;
			}
		case TextureFormat::RG:
			switch (type) {
			case Type::uint8: return GL_RG8UI;
			case Type::uint16: return GL_RG16UI;
			case Type::uint32: return GL_RG32UI;
			case Type::float32: return GL_RG32F;
			default: return GL_RG;
			}
		case TextureFormat::RGB:
			switch (type) {
			case Type::uint8: return GL_RGB8UI;
			case Type::uint16: return GL_RGB16UI;
			case Type::uint32: return GL_RGB32UI;
			case Type::float32: return GL_RGB32F;
			default: return GL_RGB;
			}
		case TextureFormat::RGBA:
			switch (type) {
			case Type::uint8: return GL_RGBA8UI;
			case Type::uint16: return GL_RGBA16UI;
			case Type::uint32: return GL_RGBA32UI;
			case Type::float32: return GL_RGBA32F;
			default: return GL_RGBA;
			}
		case TextureFormat::DEPTH_AND_STENCIL:
			return GL_DEPTH24_STENCIL8;
		}
		return GL_FALSE;
	}
	
	constexpr GLenum texture_filter_mag(TextureFilter mag_filter) {
		switch (mag_filter) {
			case TextureFilter::Nearest: return GL_NEAREST;
			case TextureFilter::Linear: return GL_LINEAR;
		}
		return GL_FALSE;
	}

	constexpr GLenum texture_filter_min(TextureFilter min_filter, MipmapFilter mipmap_filter) {
		switch (mipmap_filter) {
		case MipmapFilter::Disabled:
			switch (min_filter) {
			case TextureFilter::Nearest: return GL_NEAREST;
			case TextureFilter::Linear: return GL_LINEAR;
			}

		case MipmapFilter::Nearest:
			switch (min_filter) {
			case TextureFilter::Nearest: return GL_NEAREST_MIPMAP_NEAREST;
			case TextureFilter::Linear: return GL_LINEAR_MIPMAP_NEAREST;
			}

		case MipmapFilter::Linear:
			switch (min_filter) {
			case TextureFilter::Nearest: return GL_NEAREST_MIPMAP_LINEAR;
			case TextureFilter::Linear: return GL_LINEAR_MIPMAP_LINEAR;
			}
		}
		return GL_FALSE;
	}

	constexpr GLenum texture_wrap(TextureWrap wrap) {
		switch (wrap) {
		case TextureWrap::Repeat: return GL_REPEAT;
		case TextureWrap::MirrorRepeat: return GL_MIRRORED_REPEAT;
		case TextureWrap::Clamp: return GL_CLAMP_TO_EDGE;
		}
		return GL_FALSE;
	}
}