#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "../renderer/framebuffer.h"
#include "material.h"

namespace engine {
	class Scene {
		// (!) Layout for scene class

		// Frame buffer with related frame components
		// Camera for render position
		// Set global GPU states for frame shape and camera pos

		// Method to render to other scenes (Probably some way to retrieve texture data)

		// Following probably wont work for more specialised cases:
		// - Have array of related shaders and textures
		// - Have array of related materials
		// - Have array of objects in scene
	};
}