#pragma once

#include <vector>

#include "../engine/engine.h"

namespace tilemap {
	void init();
	void deinit();

	void set_camera_rot(const glm::vec3& rot);
	void set_camera_pos(const glm::vec3& pos);

	void set_screen_size(const glm::uvec2& size);

	void draw(const glm::vec3& pos, const glm::vec3& size);
}