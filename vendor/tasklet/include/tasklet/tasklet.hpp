#pragma once

#include <concurrentqueue.h>
#include <functional>
#include <atomic>

namespace tasklet {
class ThreadPool {
public:
  ThreadPool();
  ThreadPool(unsigned int thread_count);
  void add_task(std::function<void()> task);
  void wait();

private:
  moodycamel::ConcurrentQueue<std::function<void()>> queue;
  unsigned int thread_count;
  std::atomic<int> wait_group = 0;
  std::atomic<bool> signal = false;
};
} // namespace tasklet
