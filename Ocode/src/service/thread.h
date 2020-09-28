#pragma once

#include "typedef.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <queue>
#include <chrono>
#include <cstdarg>

#include "threadmessage.h"

namespace ocode {
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

    public:
        WorkerThread();

        virtual ~WorkerThread();

        void stop_running();

        void post_message(std::function<void()> action) {
            std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Post, action));

            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
        }
    };

    class WorkerThreadDelay : public Thread {
    private:
        std::unique_ptr<std::thread> thread;
        std::mutex mutex;
        std::condition_variable cv;

        std::queue<std::shared_ptr<ThreadMessage>> queue;

        void TimerThread();

        void ProcessThread();

    public:
        WorkerThreadDelay();

        virtual ~WorkerThreadDelay();

        void stop_running();

        void post_message(std::function<void()> action) {
            std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Post, action));

            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
            cv.notify_one();
        }
    };
}