#pragma once

#include "../application.h"

namespace ui {
	class EntityType {
	public:
		EntityType() {}
		virtual ~EntityType() {}

		virtual void update(entt::registry& registry, std::vector<entt::entity>& entities) = 0;
	};

	using TypeStorage = std::unordered_map<std::string, ui::EntityType*>;
	using EntityStorage = std::unordered_map<EntityType*, std::vector<entt::entity>>;

	struct TypeComponent {
		EntityType* type;
	};

	struct MenuEvent : ocode::Event {
		std::string name;

		MenuEvent(const std::string& name) : name(name) {}
	};

	// TODO Could probably be turned into scene class
	class Menu {
	protected:
		EntityStorage entities;

		entt::registry registry;

	public:
		virtual ~Menu() {}

		void new_type(EntityType* type);

		template<class Type, class... Args>
		entt::entity create(EntityType* type, Args&&... args) {
			entt::entity entity = registry.create();
			entities[type].push_back(entity);

			registry.emplace<TypeComponent>(entity, type);
			((Type*)type)->create(registry, entity, std::forward<Args>(args)...);

			return entity;
		}

		void destroy(entt::entity entity);

		virtual void update();
		
		template<class Type, class... Args>
		void update_component(Args&&... args) {
			Type::update(registry, std::forward<Args>(args)...);
		}
	};
}