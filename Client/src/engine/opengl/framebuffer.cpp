#include "../renderer/framebuffer.h"

#include "opengl.h"

namespace engine {
	uint32 current_texture = 0;
	uint32 current_multisample_texture = 0;
	uint32 current_renderbuffer = 0;
	uint32 current_framebuffer = 0;

	TextureBuffer::TextureBuffer(const glm::uvec2& size) {
		glGenTextures(1, &buffer_id);

		resize(size);
	}

	TextureBuffer::TextureBuffer(const Texture& texture) {
		glGenTextures(1, &buffer_id);

		set_data(texture);
	}

	TextureBuffer::~TextureBuffer() {
		glDeleteTextures(1, &buffer_id);
	}

	void TextureBuffer::use() {
		if (current_texture != buffer_id) {
			glBindTexture(GL_TEXTURE_2D, buffer_id);
			current_texture = buffer_id;
		}
	}

	const glm::uvec2 TextureBuffer::get_size() {
		return size;
	}

	void TextureBuffer::use(uint32 slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		use();
	}

	void TextureBuffer::resize(const glm::uvec2& size) {
		use();
		this->size = size;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, gl_type(Type::uint8), nullptr);
	}

	void TextureBuffer::set_data(const Texture& texture) {
		use();
		size = texture.get_size();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, gl_type(Type::uint8), texture.get_data());
	}

	MSTextureBuffer::MSTextureBuffer(const glm::uvec2& size, uint32 samples) {
		glGenTextures(1, &buffer_id);

		resize(size, samples);
	}

	MSTextureBuffer::~MSTextureBuffer() {
		glDeleteTextures(1, &buffer_id);
	}

	void MSTextureBuffer::use() {
		if (current_multisample_texture != buffer_id) {
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, buffer_id);
			current_multisample_texture = buffer_id;
		}
	}

	const glm::uvec2 MSTextureBuffer::get_size() {
		return size;
	}

	const uint32 MSTextureBuffer::get_samples() {
		return samples;
	}

	void MSTextureBuffer::use(uint32 slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		use();
	}

	void MSTextureBuffer::resize(const glm::uvec2& size, uint32 samples) {
		use();
		this->size = size;
		this->samples = samples;
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA, size.x, size.y, GL_TRUE);
	}

	DepthBuffer::DepthBuffer(const glm::uvec2& size, uint32 samples) {
		glGenRenderbuffers(1, &buffer_id);
		resize(size, samples);
	}

	DepthBuffer::~DepthBuffer() {
		glDeleteRenderbuffers(1, &buffer_id);
	}

	void DepthBuffer::use() {
		if (current_renderbuffer != buffer_id) {
			glBindRenderbuffer(GL_RENDERBUFFER, buffer_id);
			current_renderbuffer = buffer_id;
		}
	}

	void DepthBuffer::resize(const glm::uvec2& size, uint32 samples) {
		use();
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, size.x, size.y);
	}

	FrameBuffer::FrameBuffer(bool) {
		buffer_id = 0;
	}

	FrameBuffer::FrameBuffer() {
		glGenFramebuffers(1, &buffer_id);
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &buffer_id);
	}

	void FrameBuffer::use() {
		if (current_framebuffer != buffer_id) {
			glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);

			current_framebuffer = buffer_id;
		}
	}

	void FrameBuffer::use_cleared() {
		use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::set_attachment(TextureBuffer& texture, uint32 position) {
		use();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + position, GL_TEXTURE_2D, texture.buffer_id, 0);
	}

	void FrameBuffer::set_attachment(MSTextureBuffer& texture, uint32 position) {
		use();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + position, GL_TEXTURE_2D_MULTISAMPLE, texture.buffer_id, 0);
	}

	void FrameBuffer::set_attachment(DepthBuffer& depth) {
		use();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth.buffer_id);
	}

	int FrameBuffer::status() {
		use();

		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	const char* get_status() {
		const char* status;
		switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		case GL_FRAMEBUFFER_UNDEFINED:                     status = "GL_FRAMEBUFFER_UNDEFINED"; break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         status = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: status = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        status = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        status = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
		case GL_FRAMEBUFFER_UNSUPPORTED:                   status = "GL_FRAMEBUFFER_UNSUPPORTED"; break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        status = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      status = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
		default:                                           status = "NONE";
		}
		return status;
	}

	void FrameBuffer::blit(FrameBuffer& buffer) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer.buffer_id);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer_id);
		//glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, size.x, size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}
}