#include "events.h"

namespace ocode {
	ObserverHandle EventManager::_event_subscribe(HandleType<Event> handle, EventType type) {
		next_id++;
		observers[type].push_back({ handle, next_id });

		return { type, next_id };
	}

	void EventManager::_event_post(Event* event, EventType type) {
		if (observers.find(type) == observers.end()) {
			return;
			//throw "Invalid post type";
		}

		for (auto& observer : observers.at(type)) {
			observer.handle(event);
		}

		delete event;
	}

	void EventManager::event_unsubscribe(EventType type, ObserverId id) {
		auto&& _observers = observers.at(type);

		for (auto observer = _observers.begin(); observer != _observers.end(); observer++) {
			if ((*observer).id == id) {
				_observers.erase(observer);
				break;
			}
		}
	}

	void EventManager::event_unsubscribe(const ObserverHandle& handle) {
		event_unsubscribe(handle.type, handle.id);
	}
}