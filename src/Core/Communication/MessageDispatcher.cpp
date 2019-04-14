#include "MessageDispatcher.h"
#include "../BaseModule.h"

using namespace core;

MessageDispatcher::MessageDispatcher() noexcept
    : m_inputQueue(std::make_shared<MultithreadQueue<std::shared_ptr<Message>>>())
{
}

MessageDispatcher::~MessageDispatcher() noexcept
{
}

void MessageDispatcher::setup(std::vector<std::shared_ptr<BaseModule>> &modules) noexcept
{
    for (auto &module : modules) {
        auto messageTypes = module->getAcceptedMessages();
        auto &queue = module->getInputQueue();
        for (auto messageType : messageTypes) {
            m_outputQueues.insert({messageType, queue});
        }
    }
}