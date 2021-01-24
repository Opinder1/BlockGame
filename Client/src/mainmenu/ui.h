#pragma once

#include "../engine/engine.h"

namespace UI {
	class Element : public engine::Transform2D {
	private:
		engine::Material* material;
		engine::Sprite* sprite;

	public:
		Element();
		~Element();

		void update();
	};
}