#include "menu.h"

namespace ui {
	void Menu::new_type(EntityType* type) {
		entities.emplace(type, std::vector<entt::entity>{});
	}

	void Menu::destroy(entt::entity entity) {
		auto e = entities[registry.get<TypeComponent>(entity).type];
		e.erase(std::remove(e.begin(), e.end(), entity), e.end());

		registry.destroy(entity);
	}

	void Menu::update() {
		for (auto& [type, entities] : entities) {
			type->update(registry, entities);
		}
	}
}