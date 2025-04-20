#include <functional>
#include <print>
#include <thread>
#include "tasklet/tasklet.hpp"

namespace tasklet {

ThreadPool::ThreadPool() {
  this->thread_count = std::thread::hardware_concurrency() / 2;
}

ThreadPool::ThreadPool(unsigned thread_count) {
  this->thread_count = thread_count;
}

void ThreadPool::add_task(std::function<void()> task) {
  this->wait_group++;
  this->queue.enqueue(task);
}

void ThreadPool::wait() {
  for (int i = 0; i < thread_count; i++) {
    std::jthread t([&]() {
      while (wait_group != 0) {
        std::function<void()> f;
        if (queue.try_dequeue(f)) {
          f();
          this->wait_group--;
          if (this->wait_group == 0) {
            if (signal == true) {
              return;
            }
            signal = true;
            signal.notify_one();
            return;
          }
        }
      }
    });
  }
  // wait when false
  signal.wait(false);
}

} // namespace tasklet
