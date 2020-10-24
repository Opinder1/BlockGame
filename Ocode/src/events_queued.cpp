#include "events_queued.h"

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

	void EventManager::event_flush() {
		while (events.size() > 0) {
			QueuedEvent event = events.front();
			events.pop();

			//printf("Event exec: %s\n", event.event->to_string().c_str());

			auto&& _observers = observers.at(event.type);

			for (auto&& observer : observers.at(event.type)) {
				if (observer.handle(event.event)) {
					break;
				}
			}

			delete event.event;
		}
	}
}