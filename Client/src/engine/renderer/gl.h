#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace engine {
	enum class Type : glm::uint32 {
		int8,
		uint8,
		int16,
		uint16,
		int32,
		uint32,
		float32,
		float64
	};

	enum class Culling : glm::uint32 {
		Disabled, Back, Front, Both
	};

	enum class PolyMode : glm::uint32 {
		Point, Line, Fill
	};

    bool renderer_init();

	const char* get_renderer_version();

	const char* get_adapter_vendor();

	const char* get_video_adapter();

	void set_multisample(bool enabled);

	void set_depthtest(bool enabled);

	void set_alphatest(bool enabled);

	void set_culling(Culling cull_type);

	void set_polymode(PolyMode poly_mode);

	void set_viewport(glm::ivec2 pos, glm::uvec2 size);
}