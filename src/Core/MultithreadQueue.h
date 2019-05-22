#ifndef MULTITHREADQUEUE_H
#define MULTITHREADQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

namespace core
{
template <typename T>
class MultithreadQueue
{
public:
    MultithreadQueue() noexcept;
    ~MultithreadQueue() noexcept;

    void push(T value) noexcept;
    bool front(T &result) noexcept;
    bool isEmpty() const noexcept;
    void waitForPushIfEmpty(int maxSecondsWait = 0) noexcept;

private:
    std::queue<T> m_data;
    std::mutex m_dataMutex;
    std::condition_variable m_conditionVariable;
    std::mutex m_waitMutex;
};
#include "MultithreadQueue.inl"
}  // namespace core

#endif
