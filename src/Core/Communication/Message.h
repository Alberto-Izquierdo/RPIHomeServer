#ifndef MESSAGE_H
#define MESSAGE_H

#include "MessageTypes.h"

namespace core
{
class Message
{
public:
    explicit Message(MessageType type) noexcept;
    Message() = delete;
    virtual ~Message() noexcept;

    MessageType getType() const noexcept { return m_type; }

private:
    MessageType m_type;
};
}  // namespace core

#endif
