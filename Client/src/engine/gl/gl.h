#pragma once

#include <ocode.h>

namespace engine {
	enum class Type : glm::uint32 {
		int8, uint8, int16, uint16, int32, uint32, float32, float64
	};

	enum class BufferType : glm::uint32 {
		Static, Dynamic, Stream
	};

	enum class DrawType : glm::uint32 {
		Triangles, Strips, Fans, Patches, Points
	};

	enum class DrawMode : glm::uint32 {
		Fill, Line, Point
	};

	enum class CullingMode : glm::uint32 {
		Disabled, Back, Front, Both
	};

	enum class ShaderType : glm::uint32 {
		Vertex, Fragment, Geometry, Compute
	};

	enum class TextureFormat : glm::uint32 {
		R, RG, RGB, RGBA, DEPTH_AND_STENCIL
	};

	enum class TextureFilter : glm::uint32 {
		Nearest, Linear
	};

	enum class MipmapFilter : glm::uint32 {
		Disabled, Nearest, Linear
	};

	enum class TextureWrap : glm::uint32 {
		Repeat, MirrorRepeat, Clamp
	};

	struct TextureLayout {
		TextureFormat format;
		Type format_datatype;
		TextureFilter min_filter;
		TextureFilter min_mipmap_filter;
		TextureFilter mag_filter;
		TextureWrap wrap;
	};

    void renderer_init();
	void init_buffer_limits();

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