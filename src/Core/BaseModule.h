#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <Core/Communication/MessageTypes.h>
#include <Core/MultithreadQueue.h>
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
    enum Type { COMMUNICATION, GPIO, TELEGRAM_BOT, MESSAGE_GENERATOR };
    explicit BaseModule(Type type, std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> outputQueue) noexcept;
    virtual ~BaseModule() noexcept;
    explicit BaseModule() = delete;

    Type getType() const noexcept { return m_type; }

    virtual const std::string &getModuleName() const noexcept = 0;

    virtual bool init() noexcept = 0;

    virtual void update() noexcept;

    void start() noexcept;

    virtual void specificStart() noexcept = 0;

    void exit(const std::shared_ptr<Message> message) noexcept;

    virtual void specificExit() noexcept = 0;

    virtual void handleMessage(const std::shared_ptr<Message> message) noexcept;

    std::vector<MessageType> getAcceptedMessages() const noexcept;

    std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &getInputQueue() noexcept { return m_inputQueue; }

    // Delete copy/assign
    BaseModule(const BaseModule &) = delete;
    BaseModule &operator=(const BaseModule &) const = delete;

protected:
    using messageHanlderFunction = void (BaseModule::*)(const std::shared_ptr<Message>);

    void addMessageHandler(MessageType messageType, messageHanlderFunction function);

    std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> getOutputQueue() const noexcept;

    bool needsToExit() const noexcept { return m_exit.load(); }

private:
    Type m_type;
    std::unordered_map<MessageType, messageHanlderFunction, std::hash<int>> m_messageHandlers;
    std::atomic_bool m_exit;
    std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> m_inputQueue;
    std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> m_outputQueue;
};
}  // namespace core

#endif
