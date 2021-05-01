#pragma once

#include "typedef.h"

#include <functional>
#include <unordered_map>
#include <vector>

#define event_subscribe(event, function) _event_subscribe<event>([&](const event* e){ function(e); })

#define event_post(event, ...) _event_post<event>(new event(__VA_ARGS__))

#define event_copy(event, data) new event(*data)

namespace ocode {
	template<class T> using HandleType = std::function<void(const T*)>;
	using ObserverId = uint32;
	using EventType = uint64;

	struct Event {
		Event(const Event&) = delete;
		Event() {}
		virtual ~Event() {};
	};

	class ObserverHandle {
		friend class EventManager;

	private:
		EventType type;
		ObserverId id;

		ObserverHandle(const ObserverHandle&) = delete;
		ObserverHandle(EventType type, ObserverId id) : type(type), id(id) {}
	};

	class EventManager {
		friend class ObserverHandle;

		struct Observer {
			HandleType<Event> handle;
			ObserverId id;
		};

	private:
		ObserverId next_id;

		std::unordered_map<EventType, std::vector<Observer>> observers;

	protected:
		ObserverHandle _event_subscribe(HandleType<Event> handle, EventType type);

		void _event_post(Event* event, EventType type);

		void event_unsubscribe(EventType type, ObserverId id);

	public:
		EventManager(const EventManager&) = delete;
		EventManager() : next_id(0) {}

		template<class T>
		ObserverHandle _event_subscribe(HandleType<T> handle) {
			static_assert(std::is_base_of<Event, T>::value, "Derive from Event");

			return _event_subscribe(reinterpret_cast<HandleType<Event>&>(handle), typeid(T).hash_code());
		}

		template<class T>
		void _event_post(T* event) {
			static_assert(std::is_base_of<Event, T>::value, "Derive from Event");

			_event_post(event, typeid(T).hash_code());
		}

		void event_unsubscribe(const ObserverHandle& handle);
	};
}