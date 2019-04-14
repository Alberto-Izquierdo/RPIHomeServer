#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include "MessageTypes.h"
#include "../MultithreadQueue.h"
#include <unordered_map>
#include <memory>

namespace core
{
class BaseModule;
class Message;

class MessageDispatcher
{
public:
    MessageDispatcher() noexcept;
    ~MessageDispatcher() noexcept;

    void setup(std::vector<std::shared_ptr<BaseModule>> &modules) noexcept;

    std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> getInputQueue() noexcept { return m_inputQueue; }

private:
    std::unordered_map<MessageType, std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>>> m_outputQueues;
    std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> m_inputQueue;
};
}  // namespace core

#endif
