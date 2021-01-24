#include "ui.h"

namespace UI {
	Element::Element() {

	}

	Element::~Element() {
		 
	}

	void Element::update() {
		sprite->draw(position, scale, rotation);
	}
}