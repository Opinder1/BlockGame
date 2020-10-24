#pragma once

#include "typedef.h"

#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>

#define GET_TYPE(T) typeid(T).hash_code()

#define EVENT_SUBSCRIBE(event, function) event_subscribe<event>(std::bind(&function, this, std::placeholders::_1));

#define EVENT_POST(event, ...) event_post(new event(__VA_ARGS__));

namespace ocode {
	template<class T>
	using HandleType = std::function<bool(const T*)>;
	using ObserverId = uint32;
	using EventType = size_t;

	class Event {
	public:
		virtual ~Event() {};

		virtual const std::string to_string() const = 0;
	};

	class ObserverHandle {
		friend class EventManager;
		friend class EventDevice;

	private:
		EventType type;
		ObserverId id;

		ObserverHandle(const ObserverHandle&) = delete;
		ObserverHandle(EventType type, ObserverId id) : type(type), id(id) {}
	};

	class EventManager {
		friend class EventDevice;

		struct Observer {
			HandleType<Event> handle;
			ObserverId id;
		};

		struct QueuedEvent {
			Event* event;
			EventType type;
		};

	private:
		ObserverId next_id = 0;

		std::unordered_map<EventType, std::vector<Observer>> observers;

		std::queue<QueuedEvent> events;

		void event_unsubscribe(EventType type, ObserverId id);

	protected:
		void event_flush();

	public:
		EventManager(const EventManager&) = delete;
		EventManager() {}

		template<class T>
		ObserverHandle event_subscribe(HandleType<T> handle) {
			EventType type = GET_TYPE(T);

			next_id++;
			observers[type].push_back({ (HandleType<Event>&)handle, next_id });

			return { type, next_id };
		}

		void event_post(Event* event, EventType type) {
			if (observers.find(type) == observers.end()) {
				return;
				//throw new std::exception("Invalid post type");
			}

			events.push({ event, type });
		}

		template<class T>
		void event_post(T* event) {
			event_post((Event*)event, GET_TYPE(T));
		}
	};

	class EventDevice {
	private:
		EventManager* manager;

	public:
		EventDevice(EventManager* manager) : manager(manager) {}

		template<class T>
		ObserverHandle event_subscribe(HandleType<T> handle) {
			return manager->event_subscribe(handle);
		}

		template<class T>
		void event_post(T* event) {
			manager->event_post(event);
		}

		inline void disconnect(const ObserverHandle& handle) {
			manager->event_unsubscribe(handle.type, handle.id);
		}
	};
}