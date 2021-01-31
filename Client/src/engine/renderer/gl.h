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

    void renderer_init();

	void renderer_deinit();
}