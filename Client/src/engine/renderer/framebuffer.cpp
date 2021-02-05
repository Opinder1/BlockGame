#include "framebuffer.h"

#include "opengl.h"

namespace engine {
	GLenum texture_index[] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15, GL_TEXTURE16, GL_TEXTURE17, GL_TEXTURE18, GL_TEXTURE19, GL_TEXTURE20, GL_TEXTURE21, GL_TEXTURE22, GL_TEXTURE23, GL_TEXTURE24, GL_TEXTURE25, GL_TEXTURE26, GL_TEXTURE27, GL_TEXTURE28, GL_TEXTURE29, GL_TEXTURE30, GL_TEXTURE31 };
	GLenum culltype_index[] = { 0, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK };
	GLenum polymode_index[] = { GL_POINT, GL_LINE, GL_FILL };

	uint32 current_texture = 0;
	uint32 current_multisample_texture = 0;
	uint32 current_renderbuffer = 0;
	uint32 current_framebuffer = 0;

	TextureBuffer::TextureBuffer(glm::ivec2 size) {
		glGenTextures(1, &buffer_id);

		data(size);
	}

	TextureBuffer::TextureBuffer(const Texture& texture) {
		glGenTextures(1, &buffer_id);

		data(texture);
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

	void TextureBuffer::activate_slot(uint32 slot) {
		glActiveTexture(texture_index[slot]);
		use();
	}

	void TextureBuffer::data(const Texture& texture) {
		use();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		size = texture.get_size();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, gl_type(Type::uint8), texture.get_data());
	}

	void TextureBuffer::data(glm::uvec2 size) {
		use();

		this->size = size;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, gl_type(Type::uint8), nullptr);
	}

	MSTextureBuffer::MSTextureBuffer(glm::uvec2 size, uint32 samples) {
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

	void MSTextureBuffer::activate_slot(uint32 slot) {
		glActiveTexture(texture_index[slot]);
		use();
	}

	void MSTextureBuffer::resize(glm::uvec2 size, uint32 samples) {
		use();
		this->size = size;
		this->samples = samples;
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA, size.x, size.y, GL_TRUE);
	}

	DepthBuffer::DepthBuffer(glm::uvec2 size, uint32 samples) {
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

	void DepthBuffer::resize(glm::uvec2 size, uint32 samples) {
		use();
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, size.x, size.y);
	}

	FrameBuffer::FrameBuffer(glm::uvec2 size, bool is_default) : size(size) {
		if (is_default) {
			buffer_id = 0;
		}
		else {
			glGenFramebuffers(1, &buffer_id);
		}
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &buffer_id);
	}

	void FrameBuffer::use() {
		if (current_framebuffer != buffer_id) {
			glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);
			glViewport(0, 0, size.x, size.y);
			current_framebuffer = buffer_id;
		}
	}

	void FrameBuffer::resize(glm::uvec2 size) {
		this->size = size;
	}

	void FrameBuffer::blit(FrameBuffer& buffer) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer.buffer_id);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer_id);
		glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, size.x, size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	void FrameBuffer::blit() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer_id);
		glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, size.x, size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	void FrameBuffer::clear(glm::vec4 color) {
		use();
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::set_depthtest(bool enabled) {
		use();
		if (enabled) {
			glEnable(GL_DEPTH_TEST);
		}
		else {
			glDisable(GL_DEPTH_TEST);
		}
	}
	
	void FrameBuffer::set_alphatest(bool enabled) {
		use();
		if (enabled) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			glDisable(GL_BLEND);
		}
	}

	void FrameBuffer::set_culling(Culling type) {
		use();
		if (type != Culling::Disabled) {
			glEnable(GL_CULL_FACE);
			glCullFace(culltype_index[(uint32)type]);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
	}

	void FrameBuffer::set_polymode(PolyMode type) {
		use();
		glPolygonMode(GL_FRONT_AND_BACK, polymode_index[(uint32)type]);
	}

	void FrameBuffer::set_multisample(bool enabled) {
		use();
		if (enabled) {
			glEnable(GL_MULTISAMPLE);
		}
		else {
			glDisable(GL_MULTISAMPLE);
		}
	}

	FrameBufferS::FrameBufferS(glm::uvec2 size) : FrameBuffer(size, true) {

	}

	FrameBufferT::FrameBufferT(TextureBuffer& buffer) : FrameBuffer(buffer.size, false), texture(buffer) {
		use();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.buffer_id, 0);
	}

	FrameBufferM::FrameBufferM(MSTextureBuffer& buffer) : FrameBuffer(buffer.size, false), texture(buffer), depth(buffer.size, buffer.samples) {
		use();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, buffer.buffer_id, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth.buffer_id);
	}

	void FrameBufferM::resize(glm::uvec2 size, uint32 samples) {
		FrameBuffer::resize(size);
		texture.resize(size, samples);
		depth.resize(size, samples);
	}
}