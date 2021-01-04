#pragma once

#include <ocode.h>

namespace engine {
	class FrameBuffer {
	private:
		uint32 frame_buffer_id;

	public:
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer();
		~FrameBuffer();
	};
}