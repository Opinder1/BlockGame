#include "thread.h"

using namespace std::chrono_literals;

namespace ocode {
    WorkerThreadDelay::WorkerThreadDelay() {
        thread = std::unique_ptr<std::thread>(new std::thread(&WorkerThreadDelay::ProcessThread, this));
    }

    WorkerThreadDelay::~WorkerThreadDelay() {
        stop_running();
    }

    void WorkerThreadDelay::stop_running() {
        if (running) {
            std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Stop, {}));

            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(message);
                cv.notify_one();
            }

            thread->join();
        }
    }

    void WorkerThreadDelay::TimerThread() {
        std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Timer, {}));

        while (running) {
            std::this_thread::sleep_for(50ms);

            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
            cv.notify_one();
        }
    }

    void WorkerThreadDelay::ProcessThread() {
        std::thread timerThread(&WorkerThreadDelay::TimerThread, this);

        while (true) {
            std::shared_ptr<ThreadMessage> message;

            {
                std::unique_lock<std::mutex> lock(mutex);
                while (queue.empty()) {
                    cv.wait(lock);
                }

                message = queue.front();
                queue.pop();
            }

            switch (message->type) {
            case ThreadMessage::Stop:
                running = false;
                timerThread.join();
                return;

            case ThreadMessage::Post:
                message->action();
                break;

            case ThreadMessage::Timer:
                on_tick();
                break;
            }
        }
    }
}