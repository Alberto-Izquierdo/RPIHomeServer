#include "GetAvailablePinsMessage.h"

using namespace core;

GetAvailablePinsMessage::GetAvailablePinsMessage(uint64_t chatId) noexcept
    : Message(MessageType::GET_AVAILABLE_PIN_ALIASES)
    , m_chatId(chatId)
{
}

GetAvailablePinsMessage::~GetAvailablePinsMessage() noexcept
{
}
