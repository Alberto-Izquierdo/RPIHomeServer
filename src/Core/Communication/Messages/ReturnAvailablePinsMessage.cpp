#include "ReturnAvailablePinsMessage.h"

using namespace core;

ReturnAvailablePinsMessage::ReturnAvailablePinsMessage(const std::vector<std::string> &pinsAvailable,
                                                       uint64_t chatId) noexcept
    : Message(MessageType::RETURN_AVAILABLE_PIN_ALIASES)
    , m_pinsAvailable(pinsAvailable)
    , m_chatId(chatId)
{
}

ReturnAvailablePinsMessage::~ReturnAvailablePinsMessage() noexcept = default;
