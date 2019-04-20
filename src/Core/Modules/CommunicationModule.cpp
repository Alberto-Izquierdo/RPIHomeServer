#include "CommunicationModule.h"
#include "../Communication/MessageDispatcher.h"
#include "../Communication/Message.h"

using namespace core;

CommunicationModule::CommunicationModule() noexcept
    : BaseModule(Type::COMMUNICATION, nullptr)
    , m_messageDispatcher(std::make_unique<MessageDispatcher>())
{
}

CommunicationModule::~CommunicationModule() noexcept
{
}

void CommunicationModule::specificStart() noexcept
{
}

void CommunicationModule::specificExit() noexcept
{
}

void CommunicationModule::setup(const std::vector<BaseModule *> &modules) noexcept
{
    m_messageDispatcher->setup(modules);
}

void CommunicationModule::handleMessage(const std::shared_ptr<Message> message) noexcept
{
    if (message->getType() == core::MessageType::EXIT) {
        exit();
    }
    m_messageDispatcher->handleMessage(message);
}
