#pragma once

#include "typedef.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <queue>
#include <chrono>
#include <cstdarg>
#include <functional>

namespace ocode {
    struct ThreadMessage {
        enum MessageType { Stop, Post, Timer };

        uint8 type;
        std::function<void()> action;

        ThreadMessage() : type(0), action(0) {}
        ThreadMessage(uint8 type, std::function<void()>&& action) : type(type), action(action) {}
    };

    class Thread { 
    protected:
        std::atomic_bool running = true;

        virtual void on_tick() = 0;

    public:
        virtual void stop_running() = 0;
    };

    class WorkerThread : public Thread {
    private:
        std::unique_ptr<std::thread> thread;
        std::mutex mutex;

        std::queue<std::shared_ptr<ThreadMessage>> queue;

        void ProcessThread();

    protected:
        template<class Function, class Class, class... Args>
        void post_message(Function f, Class c, Args... args) {
            std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Post, std::bind(f, c, args...)));

            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
        }

    public:
        WorkerThread();

        virtual ~WorkerThread();

        void stop_running();
    };

    class WorkerThreadDelay : public Thread {
    private:
        std::unique_ptr<std::thread> thread;
        std::mutex mutex;
        std::condition_variable cv;

        std::queue<std::shared_ptr<ThreadMessage>> queue;

        void TimerThread();

        void ProcessThread();

    protected:
        template<class Function, class Class, class... Args>
        void post_message(Function f, Class c, Args... args) {
            std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Post, std::bind(f, c, args...)));

            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
            cv.notify_one();
        }

    public:
        WorkerThreadDelay();

        virtual ~WorkerThreadDelay();

        void stop_running();
    };
}