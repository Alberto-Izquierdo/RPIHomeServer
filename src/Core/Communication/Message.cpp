#include "Message.h"

using namespace core;

Message::Message(MessageType type) noexcept
    : m_type(type)
{
}

Message::~Message() noexcept = default;
