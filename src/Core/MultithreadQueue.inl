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
    auto lock = std::unique_lock<std::mutex>(m_dataMutex);
    m_data.push(value);
    m_conditionVariable.notify_one();
}

template <typename T>
T MultithreadQueue<T>::front() noexcept
{
    auto lock = std::unique_lock<std::mutex>(m_dataMutex);
    return m_data.front();
}

template <typename T>
void MultithreadQueue<T>::pop() noexcept
{
    auto lock = std::unique_lock<std::mutex>(m_dataMutex);
    m_data.pop();
}

template <typename T>
bool MultithreadQueue<T>::isEmpty() const noexcept
{
    return m_data.empty();
}

template <typename T>
void MultithreadQueue<T>::waitForPushIfEmpty() noexcept
{
    if (isEmpty()) {
        auto lock = std::unique_lock<std::mutex>(m_waitMutex);
        m_conditionVariable.wait(lock);
    }
}
