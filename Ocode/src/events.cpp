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
}