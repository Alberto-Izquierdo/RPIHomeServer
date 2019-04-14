#include "BaseModule.h"
#include "Communication/Message.h"

using namespace core;

BaseModule::BaseModule(Type type, std::shared_ptr<std::queue<std::shared_ptr<Message>>> &outputQueue) noexcept
    : m_type(type)
    , m_exit(false)
    , m_inputQueue(std::make_shared<std::queue<std::shared_ptr<Message>>>())
    , m_outputQueue(outputQueue)
{
}

BaseModule::~BaseModule()
{
}

void BaseModule::update() noexcept
{
    std::unique_lock<std::mutex> lock(*m_mutex);
    m_conditionVariable->wait(lock);
    while (!m_inputQueue->empty()) {
        handleMessage(m_inputQueue->front());
        m_inputQueue->pop();
    }
}

void BaseModule::start() noexcept
{
    specificStart();
    while (!m_exit.load()) {
        update();
    }
}

void BaseModule::exit() noexcept
{
    specificExit();
    m_exit = true;
    m_conditionVariable->notify_one();
}

void BaseModule::handleMessage(const std::shared_ptr<Message> message) noexcept
{
    auto it = m_messageHandlers.find(message->getType());
    if (it != m_messageHandlers.end()) {
        (this->*(it->second))(message);
    } else {
        // Launch error (maybe send error message back?)
    }
}

std::vector<MessageType> BaseModule::getAcceptedMessages() const noexcept
{
    std::vector<MessageType> result;
    result.reserve(m_messageHandlers.size());
    for (const auto &pair : m_messageHandlers) {
        result.push_back(pair.first);
    }
    return result;
}
