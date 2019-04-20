#include "MessageDispatcher.h"
#include "Message.h"
#include "../BaseModule.h"
#include "../MultithreadQueue.h"

using namespace core;

MessageDispatcher::MessageDispatcher() noexcept
{
}

MessageDispatcher::~MessageDispatcher() noexcept
{
}

void MessageDispatcher::setup(const std::vector<std::unique_ptr<BaseModule>> &modules) noexcept
{
    for (auto &module : modules) {
        auto messageTypes = module->getAcceptedMessages();
        auto &queue = module->getInputQueue();
        for (auto messageType : messageTypes) {
            auto it = m_outputQueues.find(messageType);
            if (it == m_outputQueues.end()) {
                m_outputQueues.insert({messageType, {queue}});
            } else {
                it->second.push_back(queue);
            }
        }
    }
}

void MessageDispatcher::handleMessage(const std::shared_ptr<Message> message) noexcept
{
    auto it = m_outputQueues.find(message->getType());
    if (it != m_outputQueues.end()) {
        for (auto &queue : it->second) {
            queue->push(message);
        }
    } else {
        // Handle error: output queue not found
    }
}
