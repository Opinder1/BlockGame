#pragma once

#include "gl.h"
#include "texture.h"

namespace engine {
	class TextureBuffer {
		friend class FrameBuffer;

	private:
		glm::uint32 buffer_id;

		glm::uvec2 size;

		void use();

	public:
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer(const glm::uvec2& size);
		TextureBuffer(const Texture& texture);
		TextureBuffer(const std::string& name) : TextureBuffer(Texture(name)) {}
		virtual ~TextureBuffer();

		const glm::uvec2 get_size();

		void use(glm::uint32 slot);

		void resize(const glm::uvec2& size);

		void set_data(const Texture& texture);
	};

	class MSTextureBuffer {
		friend class FrameBuffer;

	private:
		glm::uint32 buffer_id;

		glm::uvec2 size;
		glm::uint32 samples;

		void use();

	public:
		MSTextureBuffer(const MSTextureBuffer&) = delete;
		MSTextureBuffer(const glm::uvec2&, glm::uint32 samples = 1);
		~MSTextureBuffer();

		const glm::uvec2 get_size();
		const glm::uint32 get_samples();

		void use(glm::uint32 slot);

		void resize(const glm::uvec2&, glm::uint32 samples = 1);
	};

	class DepthBuffer {
		friend class FrameBuffer;

	private:
		glm::uint32 buffer_id;

		void use();

	public:
		DepthBuffer(const DepthBuffer&) = delete;
		DepthBuffer(const glm::uvec2&, glm::uint32 samples = 1);
		~DepthBuffer();

		void resize(const glm::uvec2&, glm::uint32 samples = 1);
	};

	class FrameBuffer {
		friend class SurfaceBase;

	private:
		glm::uint32 buffer_id;

		FrameBuffer(bool window);

	public:
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer();
		~FrameBuffer();
		 
		void use();
		void use_cleared();

		void set_attachment(TextureBuffer& texture, glm::uint32 position);
		void set_attachment(MSTextureBuffer& texture, glm::uint32 position);
		void set_attachment(DepthBuffer& depth);

		int status();
		const char* get_status();

		void blit(FrameBuffer& buffer);
	};
}