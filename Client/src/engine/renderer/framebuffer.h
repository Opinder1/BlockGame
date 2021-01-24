#pragma once

#include <ocode.h>

#include "opengl.h"

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