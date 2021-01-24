#include "buffer.h"

namespace engine {
	GLenum texture_index[] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15, GL_TEXTURE16, GL_TEXTURE17, GL_TEXTURE18, GL_TEXTURE19, GL_TEXTURE20, GL_TEXTURE21, GL_TEXTURE22, GL_TEXTURE23, GL_TEXTURE24, GL_TEXTURE25, GL_TEXTURE26, GL_TEXTURE27, GL_TEXTURE28, GL_TEXTURE29, GL_TEXTURE30, GL_TEXTURE31 };

	Buffer::Buffer(uint32 type) : buffer_type(type) {
		glGenBuffers(1, &buffer_id);
		bind();
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &buffer_id);
	}

	void Buffer::bind() {
		glBindBuffer(buffer_type, buffer_id);
	}

	const uint32 Buffer::get_id() {
		return buffer_id;
	}

	const uint32 Buffer::get_size() {
		return buffer_size;
	}

	GlobalBuffer::GlobalBuffer(uint32 id) : Buffer(GL_UNIFORM_BUFFER) {
		glBindBufferBase(GL_UNIFORM_BUFFER, id, get_id());
	}

	TextureBuffer::TextureBuffer() {
		glGenTextures(1, &buffer_id);

		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	TextureBuffer::~TextureBuffer() {
		glDeleteTextures(1, &buffer_id);
	}

	void TextureBuffer::bind() {
		glBindTexture(GL_TEXTURE_2D, buffer_id);
	}

	void TextureBuffer::use(uint32 index) {
		bind();
		glActiveTexture(texture_index[index]);
	}

	void TextureBuffer::data(const Texture& texture) {
		bind();
		glm::uvec2 size = texture.get_size();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.get_data());
	}
}