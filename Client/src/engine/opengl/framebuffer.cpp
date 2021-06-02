#include "../renderer/framebuffer.h"

#include "opengl.h"

namespace engine {
	constexpr GLenum storage_format(Format format) {
		switch (format) {
		case Format::R:
			return GL_RED;
		case Format::RG:
			return GL_RG;
		case Format::RGB:
			return GL_RGB;
		case Format::RGBA:
			return GL_RGBA;
		case Format::DEPTH_AND_STENCIL:
			return GL_DEPTH24_STENCIL8;
		default:
			return GL_FALSE;
		}
	}

	constexpr GLenum storage_type(Format format, Type type = Type::float64) {
		switch (format) {
		case Format::R:
			switch (type) {
			case Type::uint8: return GL_R8UI;
			case Type::uint16: return GL_R16UI;
			case Type::uint32: return GL_R32UI;
			case Type::float32: return GL_R32F;
			default: return GL_RED;
			}
		case Format::RG:
			switch (type) {
			case Type::uint8: return GL_RG8UI;
			case Type::uint16: return GL_RG16UI;
			case Type::uint32: return GL_RG32UI;
			case Type::float32: return GL_RG32F;
			default: return GL_RG;
			}
		case Format::RGB:
			switch (type) {
			case Type::uint8: return GL_RGB8UI;
			case Type::uint16: return GL_RGB16UI;
			case Type::uint32: return GL_RGB32UI;
			case Type::float32: return GL_RGB32F;
			default: return GL_RGB;
			}
		case Format::RGBA:
			switch (type) {
			case Type::uint8: return GL_RGBA8UI;
			case Type::uint16: return GL_RGBA16UI;
			case Type::uint32: return GL_RGBA32UI;
			case Type::float32: return GL_RGBA32F;
			default: return GL_RGBA;
			}
		case Format::DEPTH_AND_STENCIL:
			return GL_DEPTH24_STENCIL8;
		default:
			return GL_FALSE;
		}
	}

	glm::uint32 current_texture = 0;
	glm::uint32 current_multisample_texture = 0;
	glm::uint32 current_renderbuffer = 0;
	glm::uint32 current_framebuffer = 0;

	void TextureBase::_new() {
		GLEW_GET_FUN(glGenTextures)(1, &buffer_id);
	}

	void TextureBase::_delete() {
		GLEW_GET_FUN(glDeleteTextures)(1, &buffer_id);
	}

	void Texture2D::use() {
		if (current_texture != buffer_id) {
			GLEW_GET_FUN(glBindTexture)(GL_TEXTURE_2D, buffer_id);
			current_texture = buffer_id;
		}
	}

	void Texture2D::use(glm::uint32 slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		GLEW_GET_FUN(glBindTexture)(GL_TEXTURE_2D, buffer_id);
		current_texture = buffer_id;
	}

	void Texture2D::set_empty(const glm::uvec2& new_size) {
		use();

		GLEW_GET_FUN(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		GLEW_GET_FUN(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLEW_GET_FUN(glTexImage2D)(GL_TEXTURE_2D, 0, storage_type(Format::RGBA, Type::float32), new_size.x, new_size.y, 0, storage_format(Format::RGBA), gl_type(Type::uint8), nullptr);
	}

	void Texture2D::set_data(const Texture& texture) {
		use();

		// TODO complete texture settings + set border
		GLEW_GET_FUN(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		GLEW_GET_FUN(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLEW_GET_FUN(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		GLEW_GET_FUN(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glm::uvec2 size = texture.get_size();
		GLEW_GET_FUN(glTexImage2D)(GL_TEXTURE_2D, 0, storage_type(Format::RGBA, Type::float32), size.x, size.y, 0, storage_format(Format::RGBA), gl_type(Type::uint8), texture.get_data());
	}

	void Texture2DMS::use() {
		if (current_multisample_texture != buffer_id) {
			GLEW_GET_FUN(glBindTexture)(GL_TEXTURE_2D_MULTISAMPLE, buffer_id);
			current_multisample_texture = buffer_id;
		}
	}

	void Texture2DMS::use(glm::uint32 slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		GLEW_GET_FUN(glBindTexture)(GL_TEXTURE_2D_MULTISAMPLE, buffer_id);
		current_multisample_texture = buffer_id;
	}

	void Texture2DMS::set_empty(const glm::uvec2& new_size, glm::uint32 samples) {
		use();
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, storage_type(Format::RGBA, Type::uint8), new_size.x, new_size.y, GL_TRUE);
	}

	void RenderBuffer::_new() {
		glGenRenderbuffers(1, &buffer_id);
	}

	void RenderBuffer::_delete() {
		glDeleteRenderbuffers(1, &buffer_id);
	}

	void RenderBuffer::use() {
		if (current_renderbuffer != buffer_id) {
			glBindRenderbuffer(GL_RENDERBUFFER, buffer_id);
			current_renderbuffer = buffer_id;
		}
	}

	void RenderBuffer::set_empty(const glm::uvec2& new_size, glm::uint32 samples) {
		use();
		// TODO Allow for setting different depths maybe. Engine itself will most probably use 24bit depth and 8bit stencil as standard.
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, new_size.x, new_size.y);
	}

	void FrameBuffer::_new() {
		glGenFramebuffers(1, &buffer_id);
	}

	void FrameBuffer::_delete() {
		glDeleteFramebuffers(1, &buffer_id);
	}

	void FrameBuffer::use() {
		if (current_framebuffer != buffer_id) {
			glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);
			current_framebuffer = buffer_id;
		}
	}

	void FrameBuffer::clear() {
		use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::set_attachment(Texture2D& texture, glm::uint32 position) {
		use();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + position, GL_TEXTURE_2D, texture.buffer_id, 0);
	}

	void FrameBuffer::set_attachment(Texture2DMS& texture, glm::uint32 position) {
		use();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + position, GL_TEXTURE_2D_MULTISAMPLE, texture.buffer_id, 0);
	}

	void FrameBuffer::set_attachment(RenderBuffer& depth) {
		use();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth.buffer_id);
	}

	bool FrameBuffer::is_complete() {
		use();
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	const std::string_view FrameBuffer::get_status() {
		use();
		switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		case GL_FRAMEBUFFER_COMPLETE:                      return "Complete"sv;
		case GL_FRAMEBUFFER_UNDEFINED:                     return "Undefined"sv;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         return "Incomplete attachment"sv;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "Missing attachment"sv;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        return "Incomplete draw buffer"sv;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        return "Incomplete read buffer"sv;
		case GL_FRAMEBUFFER_UNSUPPORTED:                   return "Unsupported"sv;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        return "Incomplete multisample"sv;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      return "Incomplete layer targets"sv;
		default:                                           return "Unknown error"sv;
		}
	}

	void FrameBuffer::blit(FrameBuffer& buffer, Rect source, Rect dest) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer.buffer_id);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer_id);
		glBlitFramebuffer(source.pos.x, source.pos.x, source.size.x, source.size.y, dest.pos.x, dest.pos.y, dest.size.x, dest.size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	void WindowBuffer::use() {
		FrameBuffer::use();
	}

	void WindowBuffer::clear() {
		FrameBuffer::clear();
	}
}