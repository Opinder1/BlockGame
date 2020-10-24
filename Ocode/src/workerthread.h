#pragma once

#include "typedef.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <queue>
#include <chrono>

#include "events.h"

namespace ocode {
    struct ThreadEvent {
        enum MessageType : uint8 {
            Stop,
            Post,
            Timer
        };

        uint8 type;
        Event* event;
        EventType event_type;

        ThreadEvent(uint8 type) : type(type), event(NULL), event_type(0) {}
        ThreadEvent(uint8 type, Event* event, EventType event_type) : type(type), event(event), event_type(event_type) {}
    };

    class WorkerThread : public EventManager {
    private:
        std::unique_ptr<std::thread> thread;
        std::mutex mutex;
        std::condition_variable cv;

        std::queue<std::shared_ptr<ThreadEvent>> queue;

        std::atomic_bool running = true;

        void threadfunc_timer();

        void threadfunc_process();

    public:
        WorkerThread(const WorkerThread&) = delete;
        WorkerThread();
        ~WorkerThread();

        bool is_running();

        void stop_running();

        template<class T>
        void post_thread_event(T* event) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(std::make_shared<ThreadEvent>(ThreadEvent(ThreadEvent::Post, event, GET_TYPE(T))));
                cv.notify_one();
            }
        }
    };

    class TickEvent : public Event {
    public:
        const std::string to_string() const override;
    };
}