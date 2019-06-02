#include "PinOnAndOffMessage.h"

using namespace core;

PinOnAndOffMessage::PinOnAndOffMessage(const std::string &pinAlias, std::chrono::duration<int> timeToSwitchOff) noexcept
    : Message(MessageType::PIN_ON_AND_OFF)
    , m_pinAlias(pinAlias)
    , m_timeToSwitchOff(timeToSwitchOff)
{
}

PinOnAndOffMessage::~PinOnAndOffMessage() noexcept
{
}
