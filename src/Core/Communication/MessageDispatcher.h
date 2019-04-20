#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <Core/Communication/MessageTypes.h>
#include <Core/MultithreadQueue.h>
#include <unordered_map>
#include <vector>
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

    void setup(const std::vector<std::unique_ptr<BaseModule>> &modules) noexcept;

    void handleMessage(const std::shared_ptr<Message> message) noexcept;

private:
    std::unordered_map<MessageType, std::vector<std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>>>>
        m_outputQueues;
};
}  // namespace core

#endif
