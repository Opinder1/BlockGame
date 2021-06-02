#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace engine {
	enum class Type : glm::uint32 {
		int8, uint8, int16, uint16, int32, uint32, float32, float64
	};

	enum class CullingMode : glm::uint32 {
		Disabled, Back, Front, Both
	};

	enum class DrawMode : glm::uint32 {
		Fill, Line, Point
	};

    bool renderer_init();

	const std::string_view get_renderer_version();

	const std::string_view get_adapter_vendor();

	const std::string_view get_video_adapter();

	void set_multisample(bool enabled);

	void set_depthtest(bool enabled);

	void set_alphatest(bool enabled);

	void set_culling(CullingMode mode);

	void set_drawmode(DrawMode mode);

	void set_viewport(glm::ivec2 pos, glm::uvec2 size);
}