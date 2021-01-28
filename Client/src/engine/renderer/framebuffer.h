#pragma once

#include "opengl.h"
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

	protected:
		uint32 buffer_id;

		void use();

	public:
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer(const Texture& texture);
		TextureBuffer(glm::ivec2 size);
		virtual ~TextureBuffer();

		void activate_slot(uint32 index);

		void data(const Texture& texture);
		void data(glm::ivec2 size);
	};

	class MSTextureBuffer {
		friend class FrameBufferM;

	protected:
		uint32 buffer_id;

		void use();

	public:
		MSTextureBuffer(glm::ivec2 size, uint32 samples);
		~MSTextureBuffer();

		void resize(glm::ivec2 size, uint32 samples);
	};

	class DepthBuffer {
		friend class FrameBufferM;

	private:
		uint32 buffer_id;

	public:
		DepthBuffer(const DepthBuffer&) = delete;
		DepthBuffer(glm::ivec2 size, uint32 samples);
		~DepthBuffer();

		void use();

		void resize(glm::ivec2 size, uint32 samples);
	};

	class FrameBuffer {
	protected:
		uint32 buffer_id;

		FrameBuffer();

	public:
		FrameBuffer(const FrameBuffer&) = delete;
		~FrameBuffer();

		static void use_screen();
		void use();

		static void clear(glm::vec4 color);

		static void set_depthtest(bool enabled);

		static void set_alphatest(bool enabled);

		static void set_culling(Culling type);

		static void set_polymode(PolyMode type);

		static void set_multisample(bool enabled);
	};

	class FrameBufferT : public FrameBuffer {
	public:
		FrameBufferT(const TextureBuffer& buffer);
	};

	class FrameBufferM : public FrameBuffer {
	private:
		MSTextureBuffer texture;
		DepthBuffer depth;

		glm::ivec2 size;
		uint32 samples;

	public:
		FrameBufferM(glm::ivec2 size, uint32 samples = 1);

		void resize(glm::ivec2 size, uint32 samples = 1);

		void blit();
	};
}