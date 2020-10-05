#include "thread.h"

namespace ocode {
    WorkerThread::WorkerThread() {
        thread = std::unique_ptr<std::thread>(new std::thread(&WorkerThread::ProcessThread, this));
    }

    WorkerThread::~WorkerThread() {
        stop_running();

        thread->join();
    }

    void WorkerThread::stop_running() {
        if (running) {
            std::shared_ptr<ThreadMessage> message(new ThreadMessage(ThreadMessage::Stop, {}));

            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
        }
    }

    void WorkerThread::ProcessThread() {
        while (true) {
            {
                std::unique_lock<std::mutex> lock(mutex);

                while (!queue.empty()) {
                    std::shared_ptr<ThreadMessage> message = queue.front();
                    queue.pop();

                    if (message->type == ThreadMessage::Stop) {
                        running = false;
                        return;
                    }
                    else if (message->type == ThreadMessage::Post) {
                        lock.unlock();
                        message->action();
                        lock.lock();
                    }
                }
            }

            on_tick();
        }
    }
}