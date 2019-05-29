#include "PinOffMessage.h"

using namespace core;

PinOffMessage::PinOffMessage(const std::string &pinAlias) noexcept
    : Message(MessageType::PIN_OFF)
    , m_pinAlias(pinAlias)
{
}

PinOffMessage::~PinOffMessage() noexcept
{
}

