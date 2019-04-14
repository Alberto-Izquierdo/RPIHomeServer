#ifndef BASEMODULE_H
#define BASEMODULE_H

#include "Communication/MessageTypes.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace core
{
class Message;

class BaseModule
{
public:
    enum class Type { NONE };
    explicit BaseModule(Type type, std::shared_ptr<std::queue<std::shared_ptr<Message>>> &outputQueue) noexcept;
    virtual ~BaseModule();

    Type getType() const noexcept { return m_type; }

    void update() noexcept;

    void start() noexcept;

    virtual void specificStart() noexcept = 0;

    void exit() noexcept;

    virtual void specificExit() noexcept = 0;

    void handleMessage(const std::shared_ptr<Message> message) noexcept;

    std::vector<MessageType> getAcceptedMessages() const noexcept;

    std::shared_ptr<std::queue<std::shared_ptr<Message>>> &getInputQueue() noexcept { return m_inputQueue; }

protected:
    using messageHanlderFunction = void (BaseModule::*)(const std::shared_ptr<Message>);

    void addMessageHandler(MessageType, messageHanlderFunction);

private:
    Type m_type;
    std::unordered_map<MessageType, messageHanlderFunction> m_messageHandlers;
    std::atomic_bool m_exit;
    std::shared_ptr<std::condition_variable> m_conditionVariable;
    std::shared_ptr<std::mutex> m_mutex;
    // TODO: change this to multithreaded queues
    std::shared_ptr<std::queue<std::shared_ptr<Message>>> m_inputQueue;
    std::shared_ptr<std::queue<std::shared_ptr<Message>>> m_outputQueue;
};
}  // namespace core

#endif
