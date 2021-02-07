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
		friend class FrameBuffer;

	private:
		uint32 buffer_id;

		glm::uvec2 size;

		void use();

	public:
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer(glm::uvec2 size);
		TextureBuffer(const Texture& texture);
		TextureBuffer(const std::string& name) : TextureBuffer(Texture(name)) {}
		virtual ~TextureBuffer();

		const glm::uvec2 get_size();

		void activate_slot(uint32 slot);

		void data(const Texture& texture);
		void data(glm::uvec2 size);
	};

	class MSTextureBuffer {
		friend class MSFrameBuffer;

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
		friend class MSFrameBuffer;

	private:
		uint32 buffer_id;

		void use();

	public:
		DepthBuffer(const DepthBuffer&) = delete;
		DepthBuffer(glm::uvec2 size, uint32 samples = 1);
		~DepthBuffer();

		void resize(glm::uvec2 size, uint32 samples = 1);
	};

	class FrameBufferBase {
	private:
		uint32 buffer_id;

	protected:
		glm::uvec2 size;

		bool multisample;
		bool depthtest;
		bool alphatest;
		Culling culltype;
		PolyMode polymode;

		FrameBufferBase(glm::uvec2 size, bool is_default = false);

	public:
		FrameBufferBase(const FrameBufferBase&) = delete;
		~FrameBufferBase();

		void use();
		void use_cleared();

		void resize(glm::uvec2 size);

		void blit(FrameBufferBase& buffer);
		void blit();

		void set_multisample(bool value);
		void set_depthtest(bool value);
		void set_alphatest(bool value);
		void set_culling(Culling value);
		void set_polymode(PolyMode value);
	};

	class WindowFrameBuffer : public FrameBufferBase {
	public:
		WindowFrameBuffer(glm::uvec2 size);
	};

	class FrameBuffer : public FrameBufferBase {
	private:
		TextureBuffer& texture;

	public:
		FrameBuffer(TextureBuffer& buffer);
	};

	class MSFrameBuffer : public FrameBufferBase {
	private:
		MSTextureBuffer& texture;
		DepthBuffer depth;

	public:
		MSFrameBuffer(MSTextureBuffer& texture);

		void resize(glm::uvec2 size, uint32 samples = 1);
	};
}