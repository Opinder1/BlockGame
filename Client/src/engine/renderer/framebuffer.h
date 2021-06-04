#pragma once

#include "gl.h"
#include "texture.h"

namespace engine {
	class TextureBase {
		friend class FrameBuffer;

	protected:
		glm::uint32 buffer_id;

	public:
		void _new();
		void _delete();
	};

	class Texture2D : public TextureBase {
	private:
		void use();

	public:
		void use(glm::uint32 slot);

		void set_empty(const glm::uvec2& new_size);

		void set_data(const Texture& texture);
	};

	class Texture2DMS : public TextureBase {
	private:
		void use();

	public:
		void use(glm::uint32 slot);

		void set_empty(const glm::uvec2& new_size, glm::uint32 samples);
	};

	class RenderBuffer {
		friend class FrameBuffer;

	private:
		glm::uint32 buffer_id;

		void use();

	public:
		void _new();
		void _delete();

		void set_empty(const glm::uvec2& new_size, glm::uint32 samples = 0);
	};

	class FrameBuffer {
	private:
		glm::uint32 buffer_id;

	public:
		void _new();
		void _delete();
		 
		void use();

		void clear();

		void set_attachment(Texture2D& texture, glm::uint32 position = 0);
		void set_attachment(Texture2DMS& texture, glm::uint32 position = 0);
		void set_attachment(RenderBuffer& depth);

		bool is_complete();
		const std::string_view get_status();

		struct Rect {
			glm::uvec2 pos;
			glm::uvec2 size;
		};

		void blit(FrameBuffer& buffer, Rect source, Rect dest);
	};

	class WindowBuffer : private FrameBuffer {
	public:
		void use();

		void clear();
	};
}