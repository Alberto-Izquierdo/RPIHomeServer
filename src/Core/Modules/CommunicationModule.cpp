#include "CommunicationModule.h"
#include <Core/Communication/MessageDispatcher.h>
#include <Core/Communication/Message.h>

using namespace core;

CommunicationModule::CommunicationModule() noexcept
    : BaseModule(BaseModule::Type::COMMUNICATION, nullptr)
    , m_messageDispatcher(std::make_unique<MessageDispatcher>())
{
}

CommunicationModule::~CommunicationModule() noexcept = default;

bool CommunicationModule::init() noexcept
{
    return true;
}

void CommunicationModule::specificStart() noexcept
{
}

void CommunicationModule::specificExit() noexcept
{
}

void CommunicationModule::setup(const std::vector<std::unique_ptr<BaseModule>> &modules) noexcept
{
    m_messageDispatcher->setup(modules);
}

void CommunicationModule::handleMessage(const std::shared_ptr<Message> &message) noexcept
{
    if (message->getType() == core::MessageType::EXIT) {
        exit(message);
    }
    m_messageDispatcher->handleMessage(message);
}
