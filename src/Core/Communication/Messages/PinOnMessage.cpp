#include "PinOnMessage.h"

using namespace core;

PinOnMessage::PinOnMessage(const std::string &pinAlias) noexcept
    : Message(MessageType::PIN_ON)
    , m_pinAlias(pinAlias)
{
}

PinOnMessage::~PinOnMessage() noexcept = default;
