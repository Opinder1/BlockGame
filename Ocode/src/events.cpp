#include "events.h"

namespace ocode {
	void EventManager::event_unsubscribe(EventType type, ObserverId id) {
		auto&& _observers = observers.at(type);

		for (auto observer = _observers.begin(); observer != _observers.end(); observer++) {
			if ((*observer).id == id) {
				_observers.erase(observer);
				break;
			}
		}
	}

	void EventManager::event_post(Event* event, EventType type) {
		if (observers.find(type) == observers.end()) {
			return;
			//throw "Invalid post type";
		}

		for (auto& observer : observers.at(type)) {
			observer.handle(event);
		}

		delete event;
	}

	void EventDevice::disconnect(const ObserverHandle& handle) {
		manager->event_unsubscribe(handle.type, handle.id);
	}
}