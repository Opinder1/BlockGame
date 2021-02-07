#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace engine {
	enum class Type : uint32 {
		int8,
		uint8,
		int16,
		uint16,
		int32,
		uint32,
		float32,
		float64
	};

    bool renderer_init();

	const char* get_renderer_version();

	const char* get_adapter_vendor();

	const char* get_video_adapter();
}