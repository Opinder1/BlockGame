#pragma once

#include "../application.h"

namespace ui {
	struct MenuEvent : ocode::Event {
		std::string name;

		MenuEvent(const std::string& name) : name(name) {}
	};

	// TODO Could probably be turned into scene class
	class Menu {
	protected:
		entt::registry registry;

	public:
		// Menu(const std::string& scene_file);
		virtual ~Menu() {}

		virtual void update() = 0;

		template<class Type, class... Args>
		entt::entity create(Args... args) {
			return Type::create(registry, args...);
		}

		template<class Type, class... Args>
		void update_component(Args... args) {
			Type::update(registry, args...);
		}
	};
}