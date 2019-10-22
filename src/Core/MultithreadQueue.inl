#include <chrono>

template <typename T>
MultithreadQueue<T>::MultithreadQueue() noexcept = default;

template <typename T>
MultithreadQueue<T>::~MultithreadQueue() noexcept = default;

template <typename T>
void MultithreadQueue<T>::push(T value) noexcept
{
    std::lock_guard<std::mutex> lock(m_dataMutex);
    m_data.push(value);
    m_conditionVariable.notify_one();
}

template <typename T>
bool MultithreadQueue<T>::front(T &result) noexcept
{
    std::lock_guard<std::mutex> lock(m_dataMutex);
    if (!isEmpty()) {
        result = m_data.front();
        m_data.pop();
        return true;
    }
    return false;
}

template <typename T>
bool MultithreadQueue<T>::isEmpty() const noexcept
{
    return m_data.empty();
}

template <typename T>
void MultithreadQueue<T>::waitForPushIfEmpty(
    std::chrono::time_point<std::chrono::system_clock> timeUntilWakeUp) noexcept
{
    if (isEmpty()) {
        auto lock = std::unique_lock<std::mutex>(m_waitMutex);
        if (timeUntilWakeUp > std::chrono::system_clock::now()) {
            m_conditionVariable.wait_until(lock, timeUntilWakeUp);
        } else {
            m_conditionVariable.wait(lock);
        }
    }
}
