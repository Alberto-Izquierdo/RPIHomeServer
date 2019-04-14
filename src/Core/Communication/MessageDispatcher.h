#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include "MessageTypes.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <queue>

namespace core
{
class BaseModule;
class Message;
class MessageDispatcher
{
public:
    MessageDispatcher() noexcept;
    ~MessageDispatcher();

    void setup(std::vector<std::shared_ptr<BaseModule>> &modules) noexcept;

    void update() noexcept;

private:
    std::unordered_map<MessageType, std::shared_ptr<std::queue<std::shared_ptr<Message>>>> m_outputQueues;
    std::shared_ptr<std::queue<std::shared_ptr<Message>>> m_inputQueue;
};
}  // namespace core

#endif
