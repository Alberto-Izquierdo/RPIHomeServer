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

    void push(T &value) noexcept;
    T front() noexcept;
    void pop() noexcept;
    bool isEmpty() noexcept;
    void wait() noexcept;

private:
    std::queue<T> m_data;
    std::condition_variable m_conditionVariable;
    std::mutex m_mutex;
};

template <typename T>
MultithreadQueue<T>::MultithreadQueue() noexcept
{
}

template <typename T>
MultithreadQueue<T>::~MultithreadQueue() noexcept
{
}

template <typename T>
void MultithreadQueue<T>::push(T &value) noexcept
{
    auto lock = std::unique_lock<std::mutex>(m_mutex);
    m_data.push(value);
    m_conditionVariable.notify_one();
}

template <typename T>
T MultithreadQueue<T>::front() noexcept
{
    auto lock = std::unique_lock<std::mutex>(m_mutex);
    return m_data.front();
}

template <typename T>
void MultithreadQueue<T>::pop() noexcept
{
    auto lock = std::unique_lock<std::mutex>(m_mutex);
    m_data.pop();
}

template <typename T>
bool MultithreadQueue<T>::isEmpty() noexcept
{
    return m_data.empty();
}

template <typename T>
void MultithreadQueue<T>::wait() noexcept
{
    auto lock = std::unique_lock<std::mutex>(m_mutex);
    m_conditionVariable.wait(lock);
}
}  // namespace core

#endif
