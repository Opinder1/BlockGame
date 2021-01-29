#include "layer.h"

namespace engine {
	Layer::Layer() : texture({ 800, 600 }, 32), sprite(texture), frame(texture) {

	}

	void Layer::resize(glm::uvec2 size) {
		frame.resize(size, 32);
	}

	void Layer::bind() {
		frame.use();
	}

	void Layer::render() {
		sprite.set_scale({ 2, 2 });
		sprite.draw();
	}
}