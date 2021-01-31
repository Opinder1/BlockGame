#pragma once

#include "gl.h"
#include "texture.h"

namespace engine {
	enum class Culling : uint32 {
		Disabled, Back, Front, Both
	};

	enum class PolyMode : uint32 {
		Point, Line, Fill
	};

	class TextureBuffer {
		friend class FrameBufferT;

	private:
		uint32 buffer_id;

		glm::uvec2 size;

		void use();

	public:
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer(glm::ivec2 size);
		TextureBuffer(const Texture& texture);
		TextureBuffer(const std::string& name) : TextureBuffer(Texture(name)) {}
		virtual ~TextureBuffer();

		const glm::uvec2 get_size();

		void activate_slot(uint32 slot);

		void data(const Texture& texture);
		void data(glm::uvec2 size);
	};

	class MSTextureBuffer {
		friend class FrameBufferM;

	private:
		uint32 buffer_id;

		glm::uvec2 size;
		uint32 samples;

		void use();

	public:
		MSTextureBuffer(const MSTextureBuffer&) = delete;
		MSTextureBuffer(glm::uvec2 size, uint32 samples);
		~MSTextureBuffer();

		const glm::uvec2 get_size();
		const uint32 get_samples();

		void activate_slot(uint32 slot);

		void resize(glm::uvec2 size, uint32 samples);
	};

	class DepthBuffer {
		friend class FrameBufferM;

	private:
		uint32 buffer_id;

		glm::uvec2 size;
		uint32 samples;

		void use();

	public:
		DepthBuffer(const DepthBuffer&) = delete;
		DepthBuffer(glm::uvec2 size, uint32 samples = 1);
		~DepthBuffer();

		void resize(glm::uvec2 size, uint32 samples = 1);
	};

	class FrameBuffer {
	private:
		uint32 buffer_id;

	protected:
		glm::uvec2 size;

		FrameBuffer(glm::uvec2 size);

	public:
		FrameBuffer(const FrameBuffer&) = delete;
		~FrameBuffer();

		static void use_screen();
		void use();
		void resize(glm::uvec2 size);

		void blit(FrameBuffer& buffer);
		void blit();

		static void clear(glm::vec4 color);

		static void set_depthtest(bool enabled);

		static void set_alphatest(bool enabled);

		static void set_culling(Culling type);

		static void set_polymode(PolyMode type);

		static void set_multisample(bool enabled);
	};

	class FrameBufferT : public FrameBuffer {
	private:
		TextureBuffer& texture;

	public:
		FrameBufferT(TextureBuffer& buffer);
	};

	class FrameBufferM : public FrameBuffer {
	private:
		MSTextureBuffer& texture;
		DepthBuffer depth;

	public:
		FrameBufferM(MSTextureBuffer& texture);

		void resize(glm::uvec2 size, uint32 samples = 1);
	};
}