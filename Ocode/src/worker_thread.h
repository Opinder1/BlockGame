#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <queue>
#include <chrono>

#include "events.h"

#define THREAD_EVENT_POST(event, ...) thread_event_post<event>(new event(__VA_ARGS__))

namespace ocode {
    enum class ThreadEventType : uint8 {
        Stop,
        Event,
        Timer
    };

    struct ThreadEvent {
        ThreadEventType type;
        Event* event;
        EventType event_type;

        ThreadEvent(ThreadEventType type) : type(type), event(NULL), event_type(0) {}
        ThreadEvent(ThreadEventType type, Event* event, EventType event_type) : type(type), event(event), event_type(event_type) {}
    };

    class WorkerThread : protected EventManager {
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
        void thread_event_post(T* event) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(std::make_shared<ThreadEvent>(ThreadEvent(ThreadEventType::Event, event, GET_TYPE(T))));
                cv.notify_one();
            }
        }
    };

    struct TickEvent : ocode::Event {

    };
}