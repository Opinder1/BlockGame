#include "layer.h"

namespace engine {
	Layer::Layer() : buffer({ 800, 600 }), sprite(buffer), frame(buffer) {

	}

	void Layer::bind() {
		frame.use();
	}

	void Layer::render() {
		sprite.set_scale({ 2, 2 });
		sprite.draw();
	}
}