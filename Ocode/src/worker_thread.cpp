#include "worker_thread.h"

using namespace std::chrono_literals;

namespace ocode {
    WorkerThread::WorkerThread() {
        thread = std::unique_ptr<std::thread>(new std::thread(&WorkerThread::threadfunc_process, this));
    }

    WorkerThread::~WorkerThread() {
        stop_running();
    }

    bool WorkerThread::is_running() {
        return running;
    };

    void WorkerThread::stop_running() {
        if (running) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(std::make_shared<ThreadEvent>(ThreadEvent(ThreadEventType::Stop)));
                cv.notify_one();
            }

            thread->join();
        }
    }

    void WorkerThread::threadfunc_timer() {
        std::shared_ptr<ThreadEvent> message = std::make_shared<ThreadEvent>(ThreadEvent(ThreadEventType::Timer));

        while (running) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(message);
                cv.notify_one();
            }

            std::this_thread::sleep_for(50ms);
        }
    }

    void WorkerThread::threadfunc_process() {
        std::thread timerThread(&WorkerThread::threadfunc_timer, this);

        while (true) {
            std::shared_ptr<ThreadEvent> event;

            {
                std::unique_lock<std::mutex> lock(mutex);
                while (queue.empty()) {
                    cv.wait(lock);
                }

                event = queue.front();
                queue.pop();
            }

            switch (event->type) {
            case ThreadEventType::Stop:
                running = false;
                timerThread.join();
                return;

            case ThreadEventType::Event:
                _event_post(event->event, event->event_type);
                break;

            case ThreadEventType::Timer:
                event_post(TickEvent);
                break;
            }
        }
    }
}